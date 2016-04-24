#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "GameWorld.h"

#include <map>

class GameEngine
{
public:
    GameEngine(int width, int height);
    void loadDico(std::string filename);

    void update();
    void addZombie(int strength, double x, double y, Entity2D* target);
    Player* addPlayer(double x, double y);

    void shoot(char c);
    void findTarget(char c);
    bool validChar(char c);

    void draw(sf::RenderTarget* renderer);

private:
    int _worldWidth, _worldHeight;
    PhyManager _phyManager;
    GameWorld _gameWorld;

    sf::Clock _waveClock;
    int _waves, _waveDelay;

    std::vector<Player*> _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;

    std::map<int, std::vector<std::string> > _wordLengthMap;

    std::vector<std::string> _dico;
};

#endif // GAMEENGINE_H_INCLUDED
