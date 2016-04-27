#include "../../includes/GameEngine/Bullet.h"

Bullet::Bullet(double x, double y, Entity2D* target) :
    Entity2D(x, y, 2),
    _targetReached(false)
{
    _vx = target->getX()+rand()%20-10-_x;
    _vy = target->getY()+rand()%20-10-_y;

    _distToTarget = sqrt(_vx*_vx+_vy*_vy);
    _vx /= _distToTarget;
    _vy /= _distToTarget;

    _speed = 25;
    _distFromOrigin = 0;
    _targetRadius = target->getR();

    _target = target;
}

void Bullet::update()
{
    _x += _speed*_vx;
    _y += _speed*_vy;

    _lastX = _x;
    _lastY = _y;

    _distFromOrigin += _speed;

    if (_distFromOrigin+_speed >= _distToTarget)
    {
        _targetReached = true;
        _target->addLife(-1);
        _target->move(_vx*_speed*0.5, _vy*_speed*0.5);
    }
}

void Bullet::draw(sf::RenderTarget* renderer, sf::RenderTarget* bloom)
{
    const auto& tex = ResourceManager<Sprite>::instance().get("bullet");
    double w = 12;
    double h = 150;

    sf::VertexArray bullet(sf::Quads, 4);
    bullet[0].position = sf::Vector2f(_x+w*-_vy, _y+w*_vx);
    bullet[1].position = sf::Vector2f(_x+w*+_vy, _y-w*_vx);
    bullet[2].position = sf::Vector2f((_x-h*_vx)+w*_vy, (_y-h*_vy)-w*_vx);
    bullet[3].position = sf::Vector2f((_x-h*_vx)-w*_vy, (_y-h*_vy)+w*_vx);

    bullet[0].texCoords = tex->topLeft();
    bullet[1].texCoords = tex->topRight();
    bullet[2].texCoords = tex->botRight();
    bullet[3].texCoords = tex->botLeft();

    renderer->draw(bullet, tex->tex());

    h = 50;
    bullet[0].position = sf::Vector2f(_x+w*-_vy, _y+w*_vx);
    bullet[1].position = sf::Vector2f(_x+w*+_vy, _y-w*_vx);
    bullet[2].position = sf::Vector2f((_x-h*_vx)+w*_vy, (_y-h*_vy)-w*_vx);
    bullet[3].position = sf::Vector2f((_x-h*_vx)-w*_vy, (_y-h*_vy)+w*_vx);
    bloom->draw(bullet, tex->tex());
}
