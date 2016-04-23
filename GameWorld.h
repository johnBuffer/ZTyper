#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "PhyManager.h"
#include "Zombie.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"

class GameWorld
{
public:
    GameWorld();

    void addPlayer(Player* &newPlayer);
    void addZombie(Zombie* &newZombie);
    void addBullet(Bullet* &newBullet);

    void update();
    std::list<Zombie*>& getZombies() {return _zombies;}

    void draw(sf::RenderTarget* renderer);

private:
    std::list<Zombie*> _zombies;
    std::list<Bullet*> _bullets;
    std::list<Explosion> _explosions;

    std::vector<Player*> _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;

    sf::Font _font;
    sf::Text _zombieText;
    sf::RenderTexture _ground;
    sf::Texture _blood;
};

#endif // GAMEWORLD_H_INCLUDED
