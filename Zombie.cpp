#include "Zombie.h"

#include <cmath>

Zombie::Zombie(double x, double y, double r) :
    Entity2D(x, y, r),
    _target(NULL)
{

}

void Zombie::update()
{
    if (!_target)
        return;

    double vx = _target->getX()-_x;
    double vy = _target->getY()-_y;

    _targetDist = sqrt(vx*vx+vy*vy);

    _x += vx/_targetDist+0.0000001;
    _y += vy/_targetDist+0.0000001;

    _lastX = _x;
    _lastY = _y;
}
