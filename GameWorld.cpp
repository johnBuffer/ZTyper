#include "GameWorld.h"

#include <iostream>

GameWorld::GameWorld()
{
    _font.loadFromFile("font.ttf");
    _zombieText.setFont(_font);
    _zombieText.setCharacterSize(20);
    _zombieText.setColor(sf::Color::Black);
    _blood.loadFromFile("blood.png");
    _ground.create(750, 700);
    _ground.clear(sf::Color::Black);
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
        }
    }

    for (Explosion &expl : _explosions) { expl.update(); }

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
        }
        else
        {
            zomb->update();
        }
    }

    _zombies.remove_if([](Zombie* &z) { bool dead = !z->getLife(); if (dead) delete z; return dead;});
    _bullets.remove_if([](Bullet* &b) { bool done = b->isTargetReached(); if (done) {delete b;} return done; });
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
}

void GameWorld::draw(sf::RenderTarget* renderer)
{
    sf::RectangleShape drying(sf::Vector2f(750, 700));
    drying.setFillColor(sf::Color(0, 0, 0, 2));
    //_ground.draw(drying);
    _ground.display();

    sf::Sprite ground(_ground.getTexture());
    renderer->draw(ground);

    for (Bullet* &bullet : _bullets)
    {
        sf::Vector2f pos(bullet->getX(), bullet->getY());
        sf::CircleShape bulletShape(bullet->getR());
        bulletShape.setOrigin(bullet->getR(), bullet->getR());
        bulletShape.setPosition(pos);

        renderer->draw(bulletShape);
    }

    for (Player* player : _players)
    {
        sf::Vector2f pos(player->getX(), player->getY());

        sf::RectangleShape playerShape(sf::Vector2f(player->getR()*2, player->getR()*2));
        playerShape.setOrigin(player->getR(), player->getR());
        playerShape.setPosition(pos);

        sf::RectangleShape weaponShape(sf::Vector2f(10, player->getR()*1.5));
        weaponShape.setOrigin(5, player->getR()*1.5);
        weaponShape.setPosition(pos);
        weaponShape.setRotation(player->getAngle()*57.2958+90);
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

            double targetDist = player->getTargetDist();
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

    double pi = 3.14159;
    for (Explosion& expl : _explosions)
    {
        sf::VertexArray explosionsShape(sf::Quads, 40*4);

        sf::Vector2f pos(expl.getX(), expl.getY());
        double r = 1.25*expl.getR();
        for (int k(0); k<20; ++k)
        {
            double x = expl.getXp(k);
            double y = expl.getYp(k);

            for (int a(0); a<4; ++a)
            {
                double angle = 2*pi/4.0*a + 0.26*k;
                explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
                double c = 255*(100 + 2*k)/255.0;
                explosionsShape[4*k+a].color = sf::Color(c, 0, 0);
            }
        }

        for (int k(20); k<40; ++k)
        {
            double x = expl.getXp(k);
            double y = expl.getYp(k);

            for (int a(0); a<4; ++a)
            {
                double angle = 2*pi/4.0*a + 0.26*k;
                explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
                explosionsShape[4*k+a].color = sf::Color(150.0, 0, 0);
            }
        }

        renderer->draw(explosionsShape);
    }
}
