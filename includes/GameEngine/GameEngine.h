#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "GameWorld.h"

#include <map>

class GameEngine
{
public:
    GameEngine(int width, int height);

    Player*   addPlayer(double x, double y);
    bool      getGameStatus() const {return _players[0]->getLifes() > 0;}

    void      pause();
    void      shoot(char c);
    void      findTarget(char c);
    void      loadDico(std::string filename);
    void      update();
    void      addZombie(int strength, double x, double y, Entity2D* target);
    void      draw(sf::RenderTarget* renderer);

private:
    bool       validChar(char c);

    bool       _paused;
    int        _worldWidth;
    int        _worldHeight;
    PhyManager _phyManager;
    GameWorld  _gameWorld;
    int        _waves;
    int        _waveDelay;
    sf::Clock  _waveClock;

    std::vector<Player*>                     _players;
    std::map<char, std::list<Zombie*> >      _wordZombiesMap;
    std::map<int, std::vector<std::string> > _wordLengthMap;
    std::vector<std::string>                 _dico;
};

#endif // GAMEENGINE_H_INCLUDED
