#include "../../includes/GameEngine/GameWorld.h"
#include "../../includes/ResourceManager/ResourceManager.h"
#include "../../includes/GameEngine/shader.h"

#include <iostream>

GameWorld::GameWorld(int width, int height):
    _worldWidth(width),
    _worldHeight(height)
{
    _font.loadFromFile("resources/fonts/font.ttf");
    _zombieText.setFont(_font);
    _zombieText.setCharacterSize(20);
    _zombieText.setColor(sf::Color::Black);
    _paused = false;

    _ground.create(_worldWidth, _worldHeight);
    _blurTexture.create(_worldWidth, _worldHeight);
    _bloomRenderer.create(_worldWidth, _worldHeight);
    _ground.clear(sf::Color::Black);
    _blurTexture.clear(sf::Color::Black);
    _bloomRenderer.clear(sf::Color::Black);

    _soundBuffers.resize(10);

    _blurH.loadFromFile("resources/shaders/blurh.frag", sf::Shader::Fragment);
    _blurV.loadFromFile("resources/shaders/blurv.frag", sf::Shader::Fragment);

    _soundBuffers[0].loadFromFile("resources/sounds/fire1.wav");
    _soundBuffers[1].loadFromFile("resources/sounds/fire2.ogg");
    _soundBuffers[2].loadFromFile("resources/sounds/turret_rotate.wav");
    _soundBuffers[3].loadFromFile("resources/sounds/click.wav");
    _soundBuffers[4].loadFromFile("resources/sounds/plaf.wav");
    _soundBuffers[5].loadFromFile("resources/sounds/plaf2.wav");
}

void GameWorld::update()
{
    for (Player* &player : _players)
    {
        player->update();
        if (!player->isTargetLocked())
        {
            _soundManager.addSound(_soundBuffers[2], 1.f);
        }
    }

    for (Bullet* &bullet : _bullets)
    {
        bullet->update();
        if (bullet->isTargetReached())
        {
            double radius = std::min(bullet->getTargetRadius()/1.0+1, 50.0);
            _explosions.push_front(Explosion(bullet->getX(), bullet->getY(), radius));
            _soundManager.addSound(_soundBuffers[5], 0.2f);
        }
    }

    for (Explosion &expl : _explosions)
    {
        expl.update();
        if (!expl.getStatus()) {expl.draw(&_ground);}
    }

    const auto& texBlood = ResourceManager<Sprite>::instance().get("blood")->tex();
    for (Zombie* &zomb : _zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        {
            sf::Sprite blood(*texBlood);
            double w = blood.getGlobalBounds().width;
            blood.setOrigin(16, 47);
            blood.scale(2*zomb->getR()/w, 2*zomb->getR()/w);
            blood.setRotation(rand()%360);
            blood.setPosition(zomb->getX(), zomb->getY());
            _ground.draw(blood);
            _explosions.push_front(Explosion(zomb->getX(), zomb->getY(), 40+rand()%10));

            _soundManager.addSound(_soundBuffers[4]);
        }
        else { zomb->update(); }
    }

    _soundManager.update();
    _zombies.remove_if([](Zombie* &z)      { bool dead = !z->getLife(); if (dead) delete z; return dead;});
    _bullets.remove_if([](Bullet* &b)      { bool done = b->isTargetReached(); if (done) {delete b;} return done; });
    _explosions.remove_if([](Explosion &e) { return !e.getStatus(); });
}

void GameWorld::addPlayer(Player* &newPlayer)
{
    _players.push_back(newPlayer);
}

void GameWorld::addZombie(Zombie* &newZombie)
{
    _zombies.push_back(newZombie);
}

void GameWorld::addBullet(Bullet* &newBullet)
{
    _bullets.push_back(newBullet);

    _soundManager.addSound(_soundBuffers[rand()%1], 0.5f);
}

void GameWorld::shotMissed()
{
    _soundManager.addSound(_soundBuffers[3]);
}

void GameWorld::draw(sf::RenderTarget* renderer)
{
    _blurTexture.clear(sf::Color::Black);
    _bloomRenderer.clear(sf::Color::Black);

    if (_drying.getElapsedTime().asSeconds() >= 2)
    {
        sf::RectangleShape drying(sf::Vector2f(_worldWidth, _worldHeight));
        drying.setFillColor(sf::Color(0, 0, 0, 2));
        _ground.draw(drying);
        _drying.restart();
    }
    _ground.display();

    sf::Sprite ground(_ground.getTexture());
    renderer->draw(ground);

    int bulletsCount = _bullets.size();
    int i(0);
    sf::VertexArray bulletsShape(sf::Lines, bulletsCount*2);
    for (Bullet* &bullet : _bullets)
    {
        sf::Vector2f pos(bullet->getX(), bullet->getY());
        bulletsShape[2*i  ].position = pos;
        bulletsShape[2*i  ].color = sf::Color(255, 255, 0);
        bulletsShape[2*i+1].position = sf::Vector2f(pos.x-70*bullet->getVx(), pos.y-70*bullet->getVy());
        bulletsShape[2*i+1].color = sf::Color(255, 0, 0);
        i++;
    }
    _blurTexture.draw(bulletsShape);
    renderer->draw(bulletsShape);

    const auto& texTurret = ResourceManager<Sprite>::instance().get("turret")->tex();
    const auto& texBase = ResourceManager<Sprite>::instance().get("base")->tex();
    const auto& texFire = ResourceManager<Sprite>::instance().get("explosion")->tex();
    for (Player* player : _players)
    {
        sf::Vector2f pos(player->getX(), player->getY());
        double playerAngle = player->getAngle();

        sf::Sprite base(*texBase);
        base.setOrigin(65, 72);
        base.setScale(0.65, 0.65);
        base.setPosition(pos.x, pos.y);

        sf::Sprite turret(*texTurret);
        turret.setOrigin(78, 245);
        turret.setScale(0.35, 0.35);
        turret.setPosition(pos.x-player->getRecoil()*cos(playerAngle), pos.y-player->getRecoil()*sin(playerAngle));
        turret.setRotation(playerAngle*57.2958+90);

        int explosionRank = player->getExplosionRank();
        sf::Sprite fire(*texFire);
        fire.setTextureRect(sf::IntRect(50*explosionRank, 0, 50, 128));
        fire.setOrigin(26, 125);
        fire.setPosition(pos.x+60*cos(playerAngle), pos.y+60*sin(playerAngle));
        fire.setRotation(playerAngle*57.2958+90);
        fire.setScale(0.9, 0.9);
        renderer->draw(fire);

        if (explosionRank < 6) _blurTexture.draw(fire);

        if (player->getTarget())
        {
            double rTarget = player->getTarget()->getR()+10;
            sf::Vector2f posTarget(player->getTarget()->getX(), player->getTarget()->getY());
            sf::CircleShape targetShape(rTarget);
            targetShape.setOrigin(rTarget, rTarget);
            targetShape.setPosition(posTarget);
            targetShape.setFillColor(sf::Color::Green);
            renderer->draw(targetShape);

            sf::VertexArray laser(sf::Lines, 2);
            laser[0].position = pos;
            laser[0].color = sf::Color::Red;

            double targetDist = player->getTargetDist()*0.75;
            double angle = player->getAngle();
            laser[1].position = sf::Vector2f(pos.x+targetDist*cos(angle), pos.y+targetDist*sin(angle));
            laser[1].color= sf::Color(255, 0, 0, 0);

            renderer->draw(laser);
        }

        renderer->draw(base);
        renderer->draw(turret);
    }

    for (Zombie* &zomb : _zombies)
    {
        sf::Vector2f pos(zomb->getX(), zomb->getY());
        sf::CircleShape zombieShape(zomb->getR());
        zombieShape.setOrigin(zomb->getR(), zomb->getR());
        zombieShape.setPosition(pos);

        _zombieText.setString(zomb->getWord());
        double w = _zombieText.getGlobalBounds().width;
        _zombieText.setPosition(pos.x-w/2.0, pos.y-10);

        renderer->draw(zombieShape);
        renderer->draw(_zombieText);
    }

    for (Explosion& expl : _explosions) { expl.draw(renderer); }

    _blurTexture.display();
    sf::Sprite spriteBloom(_blurTexture.getTexture());
    spriteBloom.setScale(0.5, 0.5);
    _bloomRenderer.draw(spriteBloom);
    sf::Sprite spriteBloomRenderer(_bloomRenderer.getTexture());
    _bloomRenderer.draw(spriteBloomRenderer, &_blurH);
    _bloomRenderer.draw(spriteBloomRenderer, &_blurV);
    spriteBloomRenderer.setScale(2, 2);

    _bloomRenderer.display();
    renderer->draw(spriteBloomRenderer, sf::BlendAdd);
}
