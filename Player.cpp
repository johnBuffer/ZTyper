#include "Player.h"

#include <cmath>

Player::Player(double x, double y) :
    Entity2D(x, y, 30),
    _target(NULL),
    _angle(-3.14159/2.0)
{

}

bool Player::shoot(char c)
{
    if (!_target)
        return false;

    return _target->shootNextLetter(c);
}

void Player::update()
{
    if (!_target)
        return;

    if (!_target->getLife())
    {
        _target = NULL;
        std::cout << "target down" << std::endl;
        return;
    }

    double vx = _target->getX()-_x;
    double vy = _target->getY()-_y;

    double targetDist = sqrt(vx*vx+vy*vy);

    double a = acos(vx/targetDist);
    if (vy < 0) a *= -1;

    _angle += (a - _angle)/10.0;
}
