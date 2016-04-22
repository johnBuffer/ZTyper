#include "Entity2D.h"

Entity2D::Entity2D(double x, double y, double r) :
    _x(x),
    _y(y),
    _r(r)
{

}

void Entity2D::move(double x, double y)
{
    _x += x;
    _y += y;
}
