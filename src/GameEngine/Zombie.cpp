#include "../../includes/GameEngine/Zombie.h"
#include "../../includes/GameEngine/phyUtils.h"

Zombie::Zombie(std::string word, double x, double y, double r) :
    Entity2D(x, y, r),
    _target(NULL),
    _word(word)
{
    _life = word.size();
    _speed = 4.0/double(word.size());
    _sheetRank = 0;
    _r = _word.size()*10;
    _type = rand()%4;
}

Zombie::~Zombie()
{
    //std::cout << "I'm down" << std::endl;
}

bool Zombie::shootNextLetter(char c)
{
    if (c == _word[0])
    {
        _word = _word.substr(1);
        return true;
    }

    return false;

}

void Zombie::update()
{
    if (!_target)
        return;

    double vx = _target->getX()-_x;
    double vy = _target->getY()-_y;

    _targetDist = sqrt(vx*vx+vy*vy);

    _x += _speed*vx/_targetDist+0.0000001;
    _y += _speed*vy/_targetDist+0.0000001;

    _lastX = _x;
    _lastY = _y;

    _sheetRank += 0.06;

    if (_sheetRank > 4)
        _sheetRank = 0;
}

void Zombie::draw(sf::RenderTarget* renderer, sf::RenderTarget* bloom)
{
    const auto& tex = ResourceManager<Sprite>::instance().get("zombie"+numberToString(_type+1));
    sf::VertexArray zombShape(sf::Quads, 4);

    double r = _r;
    double x = _x;
    double y = _y;

    zombShape[0].position = sf::Vector2f(x-r, y-2*r);
    zombShape[1].position = sf::Vector2f(x+r, y-2*r);
    zombShape[2].position = sf::Vector2f(x+r, y);
    zombShape[3].position = sf::Vector2f(x-r, y);

    zombShape[0].color = sf::Color::White;
    zombShape[1].color = sf::Color::White;
    zombShape[2].color = sf::Color::White;
    zombShape[3].color = sf::Color::White;

    zombShape[0].texCoords = tex->topLeft(_sheetRank);
    zombShape[1].texCoords = tex->topRight(_sheetRank);
    zombShape[2].texCoords = tex->botRight(_sheetRank);
    zombShape[3].texCoords = tex->botLeft(_sheetRank);

    double smooth = 10;
    sf::VertexArray shadow(sf::TrianglesFan, smooth+1);
    shadow[0].position = sf::Vector2f(x, y);
    shadow[0].color = sf::Color(0, 0, 0);
    for (int i(1); i<smooth+1; ++i)
    {
        double a = 3.14159*2/(smooth-1)*i;
        shadow[i].position = sf::Vector2f(x+1.5*_r*cos(a), y+0.75*_r*sin(a));
        shadow[i].color = sf::Color(0, 0, 0, 0);
    }
    renderer->draw(shadow);
    renderer->draw(zombShape, tex->tex());

    /*sf::CircleShape zombieShape(_r);
    zombieShape.setOrigin(_r, _r);
    zombieShape.setPosition(_x, _y);
    renderer->draw(zombieShape);*/
}
