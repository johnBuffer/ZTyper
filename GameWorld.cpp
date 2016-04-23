#include "GameWorld.h"

#include <iostream>

GameWorld::GameWorld()
{
    _font.loadFromFile("font.ttf");
    _zombieText.setFont(_font);

    _scoreText = _zombieText;
    _accuracyText = _zombieText;
    _comboText = _zombieText;

    _zombieText.setCharacterSize(20);
    _zombieText.setColor(sf::Color::Black);
    _blood.loadFromFile("blood.png");
    _ground.create(750, 700);
    _ground.clear(sf::Color::Black);

    _soundBuffers.resize(10);

    _soundBuffers[0].loadFromFile("fire1.ogg");
    _soundBuffers[1].loadFromFile("fire2.ogg");
    _soundBuffers[2].loadFromFile("fire3.ogg");
    _soundBuffers[3].loadFromFile("click.wav");
    _soundBuffers[4].loadFromFile("plaf.wav");
    _soundBuffers[5].loadFromFile("plaf2.wav");
}

void GameWorld::update()
{
    for (Player* &player : _players) { player->update(); }
    for (Bullet* &bullet : _bullets)
    {
        bullet->update();
        if (bullet->isTargetReached())
        {
            _explosions.push_front(Explosion(bullet->getX(), bullet->getY(), 10));
            sf::Sound s(_soundBuffers[5]);
            s.setVolume(20);
            _sounds.push_back(s);
            _sounds.back().play();
        }
    }

    for (Explosion &expl : _explosions)
    {
        expl.update();

        if (!expl.getStatus())
        {
            expl.draw(&_ground);
        }
    }

    for (Zombie* &zomb : _zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        {
            sf::Sprite blood(_blood);
            double w = blood.getGlobalBounds().width;
            blood.setOrigin(16, 47);
            blood.scale(3*zomb->getR()/w, 3*zomb->getR()/w);
            blood.setRotation(rand()%360);
            blood.setPosition(zomb->getX(), zomb->getY());
            _ground.draw(blood);

            _sounds.push_back(sf::Sound(_soundBuffers[4]));
            _sounds.back().play();
        }
        else
        {
            zomb->update();
        }
    }

    _zombies.remove_if([](Zombie* &z) { bool dead = !z->getLife(); if (dead) delete z; return dead;});
    _bullets.remove_if([](Bullet* &b) { bool done = b->isTargetReached(); if (done) {delete b;} return done; });
    _explosions.remove_if([](Explosion &e) { return !e.getStatus(); });
    _sounds.remove_if([](sf::Sound &s) { return !s.getStatus(); });
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

    sf::Sound s(_soundBuffers[rand()%3]);
    s.setVolume(50);
    _sounds.push_back(s);
    _sounds.back().play();
}

void GameWorld::shotMissed()
{
    sf::Sound s(_soundBuffers[3]);
    _sounds.push_back(s);
    _sounds.back().play();
}

void GameWorld::draw(sf::RenderTarget* renderer)
{
    if (_drying.getElapsedTime().asSeconds() >= 5)
    {
        sf::RectangleShape drying(sf::Vector2f(750, 700));
        drying.setFillColor(sf::Color(0, 0, 0, 10));
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
            double rTarget = player->getTarget()->getR()*1.1;
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

    for (Explosion& expl : _explosions)
    {
        expl.draw(renderer);
    }

    _scoreText.setPosition(10, 600);
    _scoreText.setString(numberToString(_players[0]->getScore()));
    _scoreText.setColor(sf::Color::White);
    renderer->draw(_scoreText);

    _comboText.setPosition(10, 640);
    _comboText.setString(numberToString(_players[0]->getAccuracy())+" %");
    _comboText.setColor(sf::Color::White);
    renderer->draw(_comboText);
}
