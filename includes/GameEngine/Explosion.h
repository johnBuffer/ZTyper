#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Entity2D.h"

#include <SFML/Graphics.hpp>

class Explosion : public Entity2D
{
public:
    Explosion();
    Explosion(double x, double y, double r);

    double getXp(int i) const {return _xp[i];}
    double getYp(int i) const {return _yp[i];}
    bool   getStatus() const {return _status;}

    void   addLife(double) {};
    void   draw(sf::RenderTarget* renderer);
    void   onContact(Entity2D*) {}
    void   update();

private:
    double _angle, _originalR;
    int    _dispersion;

    double _vx[100];
    double _vy[100];

    double _xp[100];
    double _yp[100];

    double _ap[100];

    bool _status;
};

#endif // EXPLOSION_H_INCLUDED
