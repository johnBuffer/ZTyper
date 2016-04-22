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

    _phyManager.update();
}

void GameEngine::addZombie(double x, double y, double r)
{
    Zombie* newZombie = new Zombie(x, y);
    _zombies.push_back(newZombie);
    _phyManager.addEntity(newZombie);
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
}
