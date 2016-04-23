#include "GameEngine.h"

#include <iostream>
#include <fstream>

GameEngine::GameEngine()
{
    _phyManager = PhyManager();

    _font.loadFromFile("font.ttf");
    _zombieText.setFont(_font);
    _zombieText.setCharacterSize(20);
    _zombieText.setColor(sf::Color::Black);

    std::string alphabet = "abcdefghijklmnopqrstuvwxz";
    for (int i(0); i<26; i++)
    {
        std::list<Zombie*> l;
        _wordZombiesMap[alphabet[i]] = l;
    }

    loadDico("dico.txt");
}

void GameEngine::loadDico(std::string filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "Cannot load dictionary" << std::endl;
        return;
    }

    std::string str;
    while (std::getline(file, str))
    {
        _dico.push_back(str);
    }
}

void GameEngine::update()
{
    _wordZombiesMap.clear();

    for (Zombie* zomb : _zombies) { zomb->update(); }
    for (Player* player : _players) { player->update(); }

    for (Zombie* &zomb : _zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        {
            this->_phyManager.remove(zomb);
        }
        else
        {
            _wordZombiesMap[zomb->getWord()[0]].push_back(zomb);
        }
    }

    _zombies.remove_if([](Zombie* &z) { bool dead = !z->getLife(); if (dead) delete z; return dead;});

    _phyManager.update();
}

void GameEngine::addZombie(int strength, double x, double y, double r, Entity2D* target)
{
    int n_words = _dico.size();
    std::string word = _dico[rand()%n_words];
    Zombie* newZombie = new Zombie(word, x, y, 7*word.size());
    newZombie->setTarget(target);

    _zombies.push_back(newZombie);
    _phyManager.addEntity(newZombie);
}

Player* GameEngine::addPlayer(double x, double y)
{
    Player* newPlayer = new Player(x, y);
    _players.push_back(newPlayer);
    _phyManager.addEntity(newPlayer);

    return newPlayer;
}

void GameEngine::findTarget(char c)
{
    std::list<Zombie*>& l = _wordZombiesMap[c];
    double minDist = -1;
    Zombie* closestZombie = NULL;

    for (Zombie* &zomb : l)
    {
        double dist = _players[0]->getDistWith(*zomb);
        if (dist < minDist || minDist == -1)
        {
            minDist = dist;
            closestZombie = zomb;
        }
    }

    _players[0]->setTarget(closestZombie);
    _players[0]->shoot(c);
}

void GameEngine::draw(sf::RenderTarget* renderer)
{
    for (Zombie* &zomb : _zombies)
    {
        sf::Vector2f pos(zomb->getX(), zomb->getY());
        sf::CircleShape zombieShape(zomb->getR());
        zombieShape.setOrigin(zomb->getR(), zomb->getR());
        zombieShape.setPosition(pos);

        _zombieText.setString(zomb->getWord());
        double w = _zombieText.getGlobalBounds().width;
        _zombieText.setPosition(pos.x-w/2.0, pos.y-10);

        renderer->draw(zombieShape);
        renderer->draw(_zombieText);
    }

    for (Player* player : _players)
    {
        sf::RectangleShape playerShape(sf::Vector2f(player->getR()*2, player->getR()*2));
        playerShape.setOrigin(player->getR(), player->getR());
        playerShape.setPosition(player->getX(), player->getY());

        sf::RectangleShape weaponShape(sf::Vector2f(10, player->getR()*1.5));
        weaponShape.setOrigin(5, player->getR()*1.5);
        weaponShape.setPosition(player->getX(), player->getY());
        weaponShape.setRotation(player->getAngle()*57.2958+90);
        weaponShape.setFillColor(sf::Color(100, 100, 100));

        renderer->draw(playerShape);
        renderer->draw(weaponShape);
    }
}
