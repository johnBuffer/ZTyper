#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Entity2D.h"

class Bullet : public Entity2D
{
public:
    Bullet(double x, double y, Entity2D* target);

    bool   isTargetReached() const {return _targetReached;}
    double getVx() const {return _vx;}
    double getVy() const {return _vy;}
    double getTargetRadius() const {return _targetRadius;}

    void   onContact(Entity2D*) {}
    void   update();
    void   draw(sf::RenderTarget* renderer, sf::RenderTarget* bloom);

private:
    double    _vx, _vy, _speed;
    double    _distToTarget, _distFromOrigin, _targetRadius;
    bool      _targetReached;
    Entity2D* _target;
};

#endif // BULLET_H_INCLUDED
