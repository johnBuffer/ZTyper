#include "../../includes/GameEngine/Entity2D.h"
#include <cmath>

Entity2D::Entity2D(double x, double y, double r) :
    _x(x),
    _y(y),
    _r(r),
    _lastX(x),
    _lastY(y),
    _ax(0),
    _ay(0),
    _dt(0.016)
{

}

void Entity2D::move(double x, double y)
{
    _x += x;
    _y += y;
}

void Entity2D::updatePosition()
{
    double newX;
    double newY;

    newX = _x+(_x-_lastX)+_dt*_ax;
    newY = _y+(_y-_lastY)+_dt*_ay;

    if (!_static)
    {
        _lastX = _x;
        _lastY = _y;
        _x = newX;
        _y = newY;
    }
}

double Entity2D::getDistWith(Entity2D& e)
{
    double vx = _x-e.getX();
    double vy = _y-e.getY();

    return sqrt(vx*vx+vy*vy);
}

