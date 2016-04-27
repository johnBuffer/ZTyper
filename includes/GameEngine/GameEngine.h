#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "GameWorld.h"
#include "GUI.h"

#include <map>

class GameEngine
{
public:
    GameEngine(int width, int height);

    Player*   addPlayer(double x, double y, double baseAngle);
    bool      getGameStatus() const {return _player->getLife() > 0;}

    void      pause();
    void      shoot(char c);
    void      resetTarget() {_player->setTarget(NULL);}
    void      findTarget(char c);
    void      loadDico(std::string filename);
    void      update();
    void      addZombie(int strength, double x, double y, Entity2D* target);
    void      draw(sf::RenderTarget* renderer);

private:
    bool       _paused;
    int        _worldWidth;
    int        _worldHeight;
    GameWorld  _gameWorld;
    int        _waves;
    int        _waveDelay;
    sf::Clock  _waveClock;

    Player*                                  _player;
    std::vector<Player*>                     _allies;
    std::map<char, std::list<Zombie*> >      _wordZombiesMap;
    std::map<int, std::vector<std::string> > _wordLengthMap;
    std::vector<std::string>                 _dico;

    GUI _gui;
};

#endif // GAMEENGINE_H_INCLUDED
