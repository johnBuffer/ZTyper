#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "PhyManager.h"
#include "Zombie.h"

class GameEngine
{
public:
    GameEngine();

    void update();
    void addZombie(double x, double y, double r);

    void draw(sf::RenderTarget* renderer) const;

private:
    PhyManager _phyManager;
    std::vector<Zombie*> _zombies;
};

#endif // GAMEENGINE_H_INCLUDED
