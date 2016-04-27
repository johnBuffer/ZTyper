#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

#include "PhyManager.h"
#include "Zombie.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"
#include "phyUtils.h"
#include "SoundManager.h"

class GameWorld
{
public:
    GameWorld(int width, int height);

    void                addPlayer(Player* &newPlayer);
    void                addZombie(Zombie* &newZombie);
    void                addBullet(Bullet* &newBullet);
    void                update();
    void                shotMissed();
    void                draw(sf::RenderTarget* renderer);
    void                pause() {_paused = !_paused;}
    std::list<Zombie*>& getZombies() {return _zombies;}

private:
    int _worldWidth,                    _worldHeight;
    bool                                _paused;
    std::list<Zombie*>                  _zombies;
    std::list<Bullet*>                  _bullets;
    std::list<Explosion>                _explosions;
    std::vector<Player*>                _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;
    std::vector<sf::SoundBuffer>        _soundBuffers;

    PhyManager        _phyManager;
    SoundManager      _soundManager;
    sf::Font          _font;
    sf::Text          _zombieText;
    sf::RenderTexture _ground, _blurTexture, _bloomRenderer;
    sf::Clock         _drying;
    sf::Shader        _blurH, _blurV;

};

#endif // GAMEWORLD_H_INCLUDED
