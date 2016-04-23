#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "GameWorld.h"

#include <map>

class GameEngine
{
public:
    GameEngine();
    void loadDico(std::string filename);

    void update();
    void addZombie(int strength, double x, double y, Entity2D* target);
    Player* addPlayer(double x, double y);

    void shoot(char c);
    void findTarget(char c);
    bool validChar(char c);

    void draw(sf::RenderTarget* renderer);

private:
    PhyManager _phyManager;
    GameWorld _gameWorld;

    std::vector<Player*> _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;

    std::vector<std::string> _dico;
};

#endif // GAMEENGINE_H_INCLUDED
