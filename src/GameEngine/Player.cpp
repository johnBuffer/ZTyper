#include "../../includes/GameEngine/Player.h"

#include <cmath>

Player::Player(double x, double y) :
    Entity2D(x, y, 30),
    _lifes(3),
    _target(NULL),
    _angle(-3.14159/2.0)
{
    _score = 0;
    _combo = 0;
    _accuracy = 0;
    _hit = 0;
    _total = 0;
    _recoil = 0;
    _static = true;
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
        _hit++;
        _recoil = 20;
    }
    else
    {
        _combo = 0;
    }
    _total++;

    _accuracy = (_hit+1)/(_total+1.0);

    return hit;
}

void Player::onContact(Entity2D* e)
{
    _lifes--;
    static_cast<Zombie*>(e)->kill();
}

void Player::update()
{
    _recoil += -_recoil/2.0;

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
