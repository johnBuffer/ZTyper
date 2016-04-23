#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "PhyManager.h"
#include "Zombie.h"
#include "Player.h"

#include <map>

class GameEngine
{
public:
    GameEngine();
    void loadDico(std::string filename);

    void update();
    void addZombie(int strength, double x, double y, double r, Entity2D* target);
    Player* addPlayer(double x, double y);

    void findTarget(char c);

    void draw(sf::RenderTarget* renderer);

private:
    PhyManager _phyManager;
    std::list<Zombie*> _zombies;
    std::vector<Player*> _players;
    std::map<char, std::list<Zombie*> > _wordZombiesMap;

    sf::Font _font;
    sf::Text _zombieText;

    std::vector<std::string> _dico;
};

#endif // GAMEENGINE_H_INCLUDED