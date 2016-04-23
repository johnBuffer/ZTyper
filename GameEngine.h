#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "PhyManager.h"
#include "Zombie.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"

#include <map>

class GameEngine
{
public:
    GameEngine();
    void loadDico(std::string filename);

    void update();
    void addZombie(int strength, double x, double y, double r, Entity2D* target);
    Player* addPlayer(double x, double y);

    void shoot(char c);
    void findTarget(char c);
    bool validChar(char c);

    void draw(sf::RenderTarget* renderer);

private:
    PhyManager _phyManager;
    std::list<Zombie*> _zombies;
    std::list<Bullet*> _bullets;
    std::list<Explosion> _explosions;

    std::vector<Player*> _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;

    std::vector<std::string> _dico;

    sf::Font _font;
    sf::Text _zombieText;
    sf::RenderTexture _ground;
    sf::Texture _blood;
};

#endif // GAMEENGINE_H_INCLUDED
