#include "Zombie.h"

#include <cmath>

Zombie::Zombie(double x, double y) :
    Entity2D(x, y, 20),
    _target(NULL)
{

}

void Zombie::update()
{
    double vx = 375-_x;
    double vy = 250-_y;

    double norm = sqrt(vx*vx+vy*vy);

    _x += vx/norm+0.0000001;
    _y += vy/norm+0.0000001;

    _lastX = _x;
    _lastY = _y;
}
