#include "../../includes/GameEngine/Explosion.h"

Explosion::Explosion(double x, double y, double r) :
    Entity2D(x, y, r)
{
    _angle = 0;
    _dispersion = 6283;
    _originalR = r;

    _status = true;

    for (int i(0); i<10; i++)
    {
        _ap[i] = rand()%(_dispersion)/1000.0;

        _xp[i] = _x;
        _yp[i] = _y;

        double v_particule = (rand()%2000)/2000.0;
        _vx[i] = 10*cos(_ap[i])*(v_particule+1);
        _vy[i] = 10*sin(_ap[i])*(v_particule+1);
    }

    for (int i(10); i<40; i++)
    {
        _ap[i] = rand()%(_dispersion)/1000.0;
        _xp[i] = _x;
        _yp[i] = _y;

        double v_particule = (rand()%2000)/2000.0;
        _vx[i] = 20*cos(_ap[i])*(v_particule+1);
        _vy[i] = 20*sin(_ap[i])*(v_particule+1);
    }
}

void Explosion::update()
{
    double dt = 0.016;
    _r -= 200*dt;

    for (int i(0); i<40; i++)
    {
        _xp[i] += 2*(_vx[i])*(_r/3.0)*dt;
        _yp[i] += 2*(_vy[i])*(_r/3.0)*dt;
    }

    double ratio = (rand()%50)/100.0;

    _status = !(_r/_originalR < ratio);
}

void Explosion::draw(sf::RenderTarget* renderer, sf::Texture* tex)
{
    double pi = 3.14159;
    sf::VertexArray explosionsShape(sf::Quads, 10*4);

    //sf::Vector2f pos(_x, _y);
    double r = 1.25*_r;
    for (int k(0); k<10; ++k)
    {
        double x = getXp(k);
        double y = getYp(k);
        for (int a(0); a<4; ++a)
        {
            double angle = 2*pi/4.0*a+k;
            double c = 100+k/10.0*155;//255*(100 + 2*k)/255.0;

            explosionsShape[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
            explosionsShape[4*k+a].color = sf::Color(c, c, c);
        }

        explosionsShape[4*k  ].texCoords = sf::Vector2f(0, 0);
        explosionsShape[4*k+1].texCoords = sf::Vector2f(70, 0);
        explosionsShape[4*k+2].texCoords = sf::Vector2f(70, 76);
        explosionsShape[4*k+3].texCoords = sf::Vector2f(0, 76);
    }

    r *= 0.05;
    sf::VertexArray particles(sf::Quads, 40*4);
    for (int k(10); k<40; ++k)
    {
        double x = getXp(k);
        double y = getYp(k);

        for (int a(0); a<4; ++a)
        {
            double angle = 2*pi/4.0*a + 0.26*k;
            particles[4*k+a].position = sf::Vector2f(x+r*cos(angle), y+r*sin(angle));
            particles[4*k+a].color = sf::Color(150.0, 0, 0);
        }
    }

    renderer->draw(particles);
    renderer->draw(explosionsShape, tex);
}
