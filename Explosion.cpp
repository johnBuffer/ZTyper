#include "Explosion.h"

Explosion::Explosion(double x, double y, double r) :
    Entity2D(x, y, r)
{
    _angle = 0;
    _dispersion = 6283;

    _status = true;

    for (int i(0); i<20; i++)
    {
        double a_p = rand()%(_dispersion);
        a_p/=1000.0;

        _xp[i] = _x;
        _yp[i] = _y;

        double v_particule = (rand()%2000)/2000.0;
        _vx[i] = 10*cos(a_p)*(v_particule+1);
        _vy[i] = 10*sin(a_p)*(v_particule+1);
    }

    for (int i(20); i<40; i++)
    {
        double a_p = rand()%(_dispersion);
        a_p/=1000.0;

        _xp[i] = _x;
        _yp[i] = _y;

        double v_particule = (rand()%2000)/2000.0;
        _vx[i] = 80*cos(a_p)*(v_particule+1);
        _vy[i] = 80*sin(a_p)*(v_particule+1);
    }
}

void Explosion::update()
{
    double dt = 0.016;
    _r -= 70*dt;

    for (int i(0); i<40; i++)
    {
        _xp[i] += 2*(_vx[i])*(_r/3.0)*dt;
        _yp[i] += 2*(_vy[i])*(_r/3.0)*dt;
    }

    _status = !(_r <= 0);
}
