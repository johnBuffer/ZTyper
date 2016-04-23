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

    loadDico("dico.txt");

    _blood.loadFromFile("blood.png");
    _ground.create(750, 700);
    _ground.clear(sf::Color::Black);
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

    for (Player* &player : _players) { player->update(); }
    for (Bullet* &bullet : _bullets)
    {
        bullet->update();
        if (bullet->isTargetReached())
        {
            _explosions.push_front(Explosion(bullet->getX(), bullet->getY(), 10));
        }
    }

    for (Explosion &expl : _explosions)
    {
        expl.update();
        //_ground.draw(explosionsShape);
    }

    for (Zombie* &zomb : _zombies)
    {
        bool dead = !zomb->getLife();
        if (dead)
        {
            sf::Sprite blood(_blood);
            double w = blood.getGlobalBounds().width;
            blood.setOrigin(16, 47);
            blood.scale(2*zomb->getR()/w, 2*zomb->getR()/w);
            blood.setRotation(rand()%360);
            blood.setPosition(zomb->getX(), zomb->getY());
            _ground.draw(blood);

            this->_phyManager.remove(zomb);
        }
        else
        {
            zomb->update();
            _wordZombiesMap[zomb->getWord()[0]].push_back(zomb);
        }
    }

    _zombies.remove_if([](Zombie* &z) { bool dead = !z->getLife(); if (dead) delete z; return dead;});
    _bullets.remove_if([](Bullet* &b) { bool done = b->isTargetReached(); if (done) {delete b;} return done; });
    _explosions.remove_if([](Explosion &e) { return !e.getStatus(); });

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

void GameEngine::shoot(char c)
{
    if (_players[0]->getTarget())
    {
        if (_players[0]->shoot(c))
        {
            _bullets.push_back(new Bullet(_players[0]->getX(), _players[0]->getY(), _players[0]->getTarget()));
            _players[0]->getTarget()->move(0, -5);
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
    sf::RectangleShape drying(sf::Vector2f(750, 700));
    drying.setFillColor(sf::Color(0, 0, 0, 2));
    //_ground.draw(drying);
    _ground.display();

    sf::Sprite ground(_ground.getTexture());
    renderer->draw(ground);

    for (Bullet* &bullet : _bullets)
    {
        sf::Vector2f pos(bullet->getX(), bullet->getY());
        sf::CircleShape bulletShape(bullet->getR());
        bulletShape.setOrigin(bullet->getR(), bullet->getR());
        bulletShape.setPosition(pos);

        renderer->draw(bulletShape);
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

        if (player->getTarget())
        {
            double rTarget = player->getTarget()->getR()*1.1;
            sf::Vector2f pos(player->getTarget()->getX(), player->getTarget()->getY());
            sf::CircleShape targetShape(rTarget);
            targetShape.setOrigin(rTarget, rTarget);
            targetShape.setPosition(pos);
            targetShape.setFillColor(sf::Color::Green);
            renderer->draw(targetShape);
        }

        renderer->draw(playerShape);
        renderer->draw(weaponShape);
    }

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

    double pi = 3.14159;
    for (Explosion& expl : _explosions)
    {
        sf::VertexArray explosionsShape(sf::Quads, 40*4);

        sf::Vector2f pos(expl.getX(), expl.getY());
        double r = 1.25*expl.getR();
        for (int k(0); k<20; ++k)
        {
            double x = expl.getXp(k);
            double y = expl.getYp(k);

            for (int a(0); a<4; ++a)
            {
                double angle = 2*pi/4.0*a + 0.26*k;
                explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
                explosionsShape[4*k+a].color = sf::Color(255*(100 + 2*k)/255.0, 0, 0);
            }
        }

        for (int k(20); k<40; ++k)
        {
            double x = expl.getXp(k);
            double y = expl.getYp(k);

            for (int a(0); a<4; ++a)
            {
                double angle = 2*pi/4.0*a + 0.26*k;
                explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
                explosionsShape[4*k+a].color = sf::Color(150.0, 0, 0);
            }
        }

        renderer->draw(explosionsShape);
    }
}
