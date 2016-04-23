#include "Bullet.h"

Bullet::Bullet(double x, double y, Entity2D* target) :
    Entity2D(x, y, 2),
    _targetReached(false)
{
    _vx = target->getX()-_x;
    _vy = target->getY()-_y;
    _distToTarget = sqrt(_vx*_vx+_vy*_vy);
    _vx /= _distToTarget;
    _vy /= _distToTarget;

    _speed = 20;
    _distFromOrigin = 0;
}

void Bullet::update()
{
    _x += _speed*_vx;
    _y += _speed*_vy;

    _lastX = _x;
    _lastY = _y;

    _distFromOrigin += _speed;

    if (_distFromOrigin >= _distToTarget)
        _targetReached = true;
}
