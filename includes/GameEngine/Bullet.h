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

    void   onContact(Entity2D*) {}
    void   update();

private:
    double _vx, _vy, _speed;
    double _distToTarget, _distFromOrigin;
    bool   _targetReached;
};

#endif // BULLET_H_INCLUDED
