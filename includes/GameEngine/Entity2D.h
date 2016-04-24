#ifndef ENTITY2D_H_INCLUDED
#define ENTITY2D_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdlib>

class Entity2D
{
public :
    Entity2D(double x, double y, double r);

    double getX() const {return _x;}
    double getY() const {return _y;}
    double getR() const {return _r;}

    double getDistWith(Entity2D& e);

    void move(double x, double y);
    void setPosition(double x, double y);

    virtual void onContact()=0;

    void updatePosition();

protected:
    double _x, _y, _r;
    double _lastX, _lastY;
    double _ax, _ay;
    double _dt;

    bool _static;
};

#endif // ENTITY2D_H_INCLUDED
