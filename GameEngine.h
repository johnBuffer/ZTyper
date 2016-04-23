#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "PhyManager.h"
#include "Zombie.h"
#include "Player.h"

class GameEngine
{
public:
    GameEngine();

    void update();
    void addZombie(double x, double y, double r, Entity2D* target);
    Player* addPlayer(double x, double y);

    void findTarget();

    void draw(sf::RenderTarget* renderer) const;

private:
    PhyManager _phyManager;
    std::list<Zombie*> _zombies;
    std::vector<Player*> _players;
};

#endif // GAMEENGINE_H_INCLUDED
