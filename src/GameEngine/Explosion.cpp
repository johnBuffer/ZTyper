#include "../../includes/GameEngine/Explosion.h"

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
        _vx[i] = 50*cos(a_p)*(v_particule+1);
        _vy[i] = 50*sin(a_p)*(v_particule+1);
    }

    for (int i(20); i<40; i++)
    {
        double a_p = rand()%(_dispersion);
        a_p/=1000.0;

        _xp[i] = _x;
        _yp[i] = _y;

        double v_particule = (rand()%2000)/2000.0;
        _vx[i] = 100*cos(a_p)*(v_particule+1);
        _vy[i] = 100*sin(a_p)*(v_particule+1);
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

    _status = !(_r <= 2);
}

void Explosion::draw(sf::RenderTarget* renderer)
{
    double pi = 3.14159;
    sf::VertexArray explosionsShape(sf::Quads, 40*4);

    sf::Vector2f pos(_x, _y);
    double r = 1.25*_r;
    for (int k(0); k<20; ++k)
    {
        double x = getXp(k);
        double y = getYp(k);

        for (int a(0); a<4; ++a)
        {
            double angle = 2*pi/4.0*a + 0.26*k;
            explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
            double c = 255*(100 + 2*k)/255.0;
            explosionsShape[4*k+a].color = sf::Color(c, 0, 0);
        }
    }

    for (int k(20); k<40; ++k)
    {
        double x = getXp(k);
        double y = getYp(k);

        for (int a(0); a<4; ++a)
        {
            double angle = 2*pi/4.0*a + 0.26*k;
            explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
            explosionsShape[4*k+a].color = sf::Color(150.0, 0, 0);
        }
    }

    renderer->draw(explosionsShape);
}
