#ifndef ENTITY2D_H_INCLUDED
#define ENTITY2D_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceManager.h"

class Entity2D
{
public :
    Entity2D(double x, double y, double r);
    virtual ~Entity2D();

    double getX() const {return _x;}
    double getY() const {return _y;}
    double getR() const {return _r;}
    double getDistWith(Entity2D& e);

    int    getLife() {return _life;}
    void   addLife(double d) {_life += d;}
    void   kill() {_life = 0;}

    void   move(double x, double y);
    void   setPosition(double x, double y);
    void   updatePosition();

    virtual void onContact(Entity2D*)=0;

protected:
    int _life;
    double _x, _y, _r;
    double _lastX, _lastY;
    double _ax, _ay;
    double _dt;
    bool   _static;
};

#endif // ENTITY2D_H_INCLUDED
