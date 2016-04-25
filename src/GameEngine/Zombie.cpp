#include "../../includes/GameEngine/Zombie.h"

Zombie::Zombie(std::string word, double x, double y, double r) :
    Entity2D(x, y, r),
    _target(NULL),
    _word(word)
{
    _speed = 6.0/double(word.size());
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
}
