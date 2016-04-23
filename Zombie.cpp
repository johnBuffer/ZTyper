#include "Zombie.h"

Zombie::Zombie(std::string word, double x, double y, double r) :
    Entity2D(x, y, r),
    _target(NULL),
    _word(word)
{

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

    _x += 0.3*vx/_targetDist+0.0000001;
    _y += 0.3*vy/_targetDist+0.0000001;

    _lastX = _x;
    _lastY = _y;
}
