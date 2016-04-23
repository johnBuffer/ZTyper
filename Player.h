#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity2D.h"
#include "Zombie.h"

class Player : public Entity2D
{
public:
    Player(double x, double y);
    void setTarget(Zombie* z) {_target = z;};

    double getAngle() const {return _angle;}

    void update();

private:
    Zombie* _target;

    double _angle;

};

#endif // PLAYER_H_INCLUDED
