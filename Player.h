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
    double getTargetDist() const {return _targetDist;}
    Zombie* getTarget() const {return _target;}

    bool shoot(char c);
    void update();

private:
    Zombie* _target;
    double _score, _combo;
    double _angle, _targetDist;

};

#endif // PLAYER_H_INCLUDED
