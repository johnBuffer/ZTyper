#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Entity2D.h"

#include <SFML/Graphics.hpp>

class Explosion : public Entity2D
{
public:
    Explosion();
    Explosion(double x, double y, double r);

    void update();

    double getXp(int i) const {return _xp[i];}
    double getYp(int i) const {return _yp[i];}

    void draw(sf::RenderTarget* renderer);

    bool getStatus() const {return _status;}

private:
    double _angle;
    int _dispersion;

    double _vx[100];
    double _vy[100];

    double _xp[100];
    double _yp[100];

    bool _status;
};

#endif // EXPLOSION_H_INCLUDED
