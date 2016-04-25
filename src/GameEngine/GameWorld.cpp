#include "../../includes/GameEngine/GameWorld.h"

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

    _blood.loadFromFile("resources/textures/blood.png");

    _ground.create(_worldWidth, _worldHeight);
    _ground.clear(sf::Color::Black);

    _soundBuffers.resize(10);

    _soundBuffers[0].loadFromFile("resources/sounds/fire1.wav");
    _soundBuffers[1].loadFromFile("resources/sounds/fire2.ogg");
    _soundBuffers[2].loadFromFile("resources/sounds/fire3.ogg");
    _soundBuffers[3].loadFromFile("resources/sounds/click.wav");
    _soundBuffers[4].loadFromFile("resources/sounds/plaf.wav");
    _soundBuffers[5].loadFromFile("resources/sounds/plaf2.wav");
}

void GameWorld::update()
{
    for (Player* &player : _players) { player->update(); }
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
        if (!expl.getStatus()) {expl.draw(&_ground, &_blood);}
    }

    for (Zombie* &zomb : _zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        {
            sf::Sprite blood(_blood);
            double w = blood.getGlobalBounds().width;
            blood.setOrigin(16, 47);
            blood.scale(2*zomb->getR()/w, 2*zomb->getR()/w);
            blood.setRotation(rand()%360);
            blood.setPosition(zomb->getX(), zomb->getY());
            _ground.draw(blood);

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
        bulletsShape[2*i+1].position = sf::Vector2f(pos.x-20*bullet->getVx(), pos.y-20*bullet->getVy());
        bulletsShape[2*i+1].color = sf::Color(255, 0, 0);
        i++;
    }
    renderer->draw(bulletsShape);

    for (Player* player : _players)
    {
        sf::Vector2f pos(player->getX(), player->getY());
        double playerAngle = player->getAngle();

        sf::RectangleShape playerShape(sf::Vector2f(player->getR()*2, player->getR()*2));
        playerShape.setOrigin(player->getR(), player->getR());
        playerShape.setPosition(pos);

        sf::RectangleShape weaponShape(sf::Vector2f(10, player->getR()*1.5));
        weaponShape.setOrigin(5, player->getR()*1.5);
        weaponShape.setPosition(pos.x-player->getRecoil()*cos(playerAngle), pos.y-player->getRecoil()*sin(playerAngle));
        weaponShape.setRotation(playerAngle*57.2958+90);
        weaponShape.setFillColor(sf::Color(100, 100, 100));

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
            laser[0].color = sf::Color::Green;

            double targetDist = player->getTargetDist()*0.5;
            double angle = player->getAngle();
            laser[1].position = sf::Vector2f(pos.x+targetDist*cos(angle), pos.y+targetDist*sin(angle));
            laser[1].color= sf::Color(0, 255, 0, 0);

            renderer->draw(laser);
        }

        renderer->draw(playerShape);
        renderer->draw(weaponShape);
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

    for (Explosion& expl : _explosions) { expl.draw(renderer, &_blood); }
}
