#include "../../includes/GameEngine/GameEngine.h"
#include "../../includes/ResourceManager/ResourceManager.h"

#include <iostream>
#include <fstream>

GameEngine::GameEngine(int width, int height):
    _worldWidth(width),
    _worldHeight(height),
    _gameWorld(width, height),
    _player(new Player(width/2, height-100)),
    _gui(_player, width, height)
{
    _phyManager = PhyManager();
    _waves = 0;
    _waveDelay = rand()%2;
    _paused = false;
    _gameWorld.addPlayer(_player);
    _phyManager.addEntity(_player);

    ResourceManager<Sprite>::instance().loadAll();

    loadDico("resources/texts/dico.txt");
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

void GameEngine::pause()
{
    _paused = !_paused;
    _gui.pause();
}

void GameEngine::update()
{
    if (_paused)
        return;

    if (_waveClock.getElapsedTime().asMilliseconds() >= _waveDelay)
    {
        _waves++;
        int strength = rand()%5+2;
        if (!(_waves%15))
        {
            strength = rand()%10+5;
        }
        addZombie(strength, rand()%_worldWidth, -strength*10, _player);

        _waveDelay = 1000;
        _waveClock.restart();
    }

    _wordZombiesMap.clear();

    auto zombies = _gameWorld.getZombies();
    for (Zombie* &zomb : zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        { this->_phyManager.remove(zomb); }
        else
        { _wordZombiesMap[zomb->getWord()[0]].push_back(zomb); }
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
    _allies.push_back(newPlayer);
    _phyManager.addEntity(newPlayer);

    _gameWorld.addPlayer(newPlayer);

    return newPlayer;
}

void GameEngine::shoot(char c)
{
    if (_paused)
        return;

    if (_player->getTarget())
    {
        if (_player->shoot(c))
        {
            Bullet* newBullet = new Bullet(_player->getX(), _player->getY(), _player->getTarget());
            _gameWorld.addBullet(newBullet);

            _player->getTarget()->move(0, -10);
        }
        else {_gameWorld.shotMissed();}
    }
    else
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
            double dist = _player->getDistWith(*zomb);
            if (dist < minDist || minDist == -1)
            {
                minDist = dist;
                closestZombie = zomb;
            }
        }

        _player->setTarget(closestZombie);
        shoot(c);
    }
}

void GameEngine::draw(sf::RenderTarget* renderer)
{
    _gameWorld.draw(renderer);
    _gui.draw(renderer);
}
