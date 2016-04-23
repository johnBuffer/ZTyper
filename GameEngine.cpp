#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine()
{
    _phyManager = PhyManager();
}

void GameEngine::update()
{
    for (Zombie* zomb : _zombies)
    {
        zomb->update();
    }

    for (Player* player : _players)
    {
        player->update();
    }

    _zombies.remove_if([](Zombie* &z) { return z->getLife();});

    _phyManager.update();
}

void GameEngine::addZombie(double x, double y, double r, Entity2D* target)
{
    Zombie* newZombie = new Zombie(x, y, r);
    newZombie->setTarget(target);

    _zombies.push_back(newZombie);
    _phyManager.addEntity(newZombie);
}

Player* GameEngine::addPlayer(double x, double y)
{
    Player* newPlayer = new Player(x, y);
    _players.push_back(newPlayer);
    _phyManager.addEntity(newPlayer);

    return newPlayer;
}

void GameEngine::findTarget()
{
    _players[0]->setTarget(_zombies.front());
}

void GameEngine::draw(sf::RenderTarget* renderer) const
{
    for (Zombie* zomb : _zombies)
    {
        sf::CircleShape zombieShape(zomb->getR());
        zombieShape.setOrigin(zomb->getR(), zomb->getR());
        zombieShape.setPosition(zomb->getX(), zomb->getY());

        renderer->draw(zombieShape);
    }

    for (Player* player : _players)
    {
        sf::RectangleShape playerShape(sf::Vector2f(player->getR()*2, player->getR()*2));
        playerShape.setOrigin(player->getR(), player->getR());
        playerShape.setPosition(player->getX(), player->getY());

        sf::RectangleShape weaponShape(sf::Vector2f(10, player->getR()*1.5));
        weaponShape.setOrigin(5, player->getR()*1.5);
        weaponShape.setPosition(player->getX(), player->getY());
        weaponShape.setRotation(player->getAngle()*57.2958+90);
        weaponShape.setFillColor(sf::Color(100, 100, 100));

        renderer->draw(playerShape);
        renderer->draw(weaponShape);
    }
}
