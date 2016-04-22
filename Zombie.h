#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include "Entity2D.h"

#include <string>
#include <iostream>

class Zombie : public Entity2D
{
public:
    Zombie(double x, double y);

    void update();

    Entity2D* getTarget() const {return _target;}

private:
    Entity2D* _target;
    std::string _word;

};

#endif // ZOMBIE_H_INCLUDED
