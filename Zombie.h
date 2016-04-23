#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include "Entity2D.h"

#include <string>
#include <iostream>

class Zombie : public Entity2D
{
public:
    Zombie(double x, double y, double r);
    void setTarget(Entity2D* target) {_target = target;}

    void update();

    Entity2D* getTarget() const {return _target;}
    double getTargetDist() const {return _targetDist;}
    int getLife() const {return _word.size();}

private:
    Entity2D* _target;
    double _targetDist;
    std::string _word;

};

#endif // ZOMBIE_H_INCLUDED
