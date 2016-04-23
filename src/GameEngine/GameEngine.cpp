#include "GameEngine.h"

#include <iostream>
#include <fstream>

GameEngine::GameEngine()
{
    _phyManager = PhyManager();
    _waves = 0;
    _waveDelay = rand()%2;

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
        _wordLengthMap[str.size()].push_back(str);
    }
}

void GameEngine::update()
{
    if (_waveClock.getElapsedTime().asSeconds() >= _waveDelay)
    {
        _waves++;
        int strength = rand()%6 + 1;
        if (!(_waves%15))
        {
            strength = rand()%5 + 10;
        }

        addZombie(strength, rand()%750, -strength*10, _players[0]);
        _waveDelay = rand()%strength/2+1;

        _waveClock.restart();
    }

    _wordZombiesMap.clear();

    auto zombies = _gameWorld.getZombies();
    for (Zombie* &zomb : zombies)
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

    _gameWorld.update();

    _phyManager.update();
}

void GameEngine::addZombie(int strength, double x, double y, Entity2D* target)
{
    int n_words = _wordLengthMap[strength].size();
    std::string word = _wordLengthMap[strength][rand()%n_words];
    Zombie* newZombie = new Zombie(word, x, y, 10*word.size());
    newZombie->setTarget(target);

    _gameWorld.addZombie(newZombie);

    _phyManager.addEntity(newZombie);
}

Player* GameEngine::addPlayer(double x, double y)
{
    Player* newPlayer = new Player(x, y);
    _players.push_back(newPlayer);
    _phyManager.addEntity(newPlayer);

    _gameWorld.addPlayer(newPlayer);

    return newPlayer;
}

void GameEngine::shoot(char c)
{
    if (_players[0]->getTarget())
    {
        if (_players[0]->shoot(c))
        {
            Bullet* newBullet = new Bullet(_players[0]->getX(), _players[0]->getY(), _players[0]->getTarget());
            _gameWorld.addBullet(newBullet);

            _players[0]->getTarget()->move(0, -5);
        }
        else
        {
            _gameWorld.shotMissed();
        }
    }
    else if (validChar(c))
    {
        findTarget(c);
    }
}

void GameEngine::findTarget(char c)
{
    Zombie* closestZombie = NULL;
    if (_wordZombiesMap.find(c) != _wordZombiesMap.end())
    {
        std::list<Zombie*>& l = _wordZombiesMap[c];
        double minDist = -1;

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
        shoot(c);
    }
}

bool GameEngine::validChar(char c)
{
    bool az = c >= 97 && c < 128;
    bool accents = c < 0;

    return az || accents;
}

void GameEngine::draw(sf::RenderTarget* renderer)
{
    _gameWorld.draw(renderer);
}
