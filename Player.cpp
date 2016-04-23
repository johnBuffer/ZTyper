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
    bool hit = false;
    if (!_target)
        return hit;

    hit = _target->shootNextLetter(c);

    if (hit)
    {
        _combo++;
        _score++;
    }
    else
    {
        _combo = 0;
    }

    return hit;
}

void Player::update()
{
    if (!_target)
        return;

    if (!_target->getLife())
    {
        _target = NULL;
        return;
    }

    double vx = _target->getX()-_x;
    double vy = _target->getY()-_y;

    _targetDist = sqrt(vx*vx+vy*vy);

    double a = acos(vx/_targetDist);
    if (vy < 0) a *= -1;

    _angle += (a - _angle)/5.0;
}
