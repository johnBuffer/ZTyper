#include "../../includes/GameEngine/Bullet.h"

Bullet::Bullet(double x, double y, Entity2D* target) :
    Entity2D(x, y, 2),
    _targetReached(false)
{
    _vx = target->getX()+rand()%20-10-_x;
    _vy = target->getY()+rand()%20-10-_y;

    _distToTarget = sqrt(_vx*_vx+_vy*_vy);
    _vx /= _distToTarget;
    _vy /= _distToTarget;

    _speed = 25;
    _distFromOrigin = 0;
    _targetRadius = target->getR();
}

void Bullet::update()
{
    _x += _speed*_vx;
    _y += _speed*_vy;

    _lastX = _x;
    _lastY = _y;

    _distFromOrigin += _speed;

    if (_distFromOrigin+_speed >= _distToTarget)
        _targetReached = true;
}
