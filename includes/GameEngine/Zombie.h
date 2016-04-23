#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include "Entity2D.h"

#include <string>
#include <iostream>

class Zombie : public Entity2D
{
public:
    Zombie(std::string word, double x, double y, double r);

    ~Zombie();

    void setTarget(Entity2D* target) {_target = target;}
    bool shootNextLetter(char c);
    void update();

    Entity2D* getTarget() const {return _target;}
    double getTargetDist() const {return _targetDist;}
    int getLife() const {return _word.size();}
    std::string getWord() const {return _word;}

private:
    Entity2D* _target;
    double _targetDist, _speed;
    std::string _word;

};

#endif // ZOMBIE_H_INCLUDED
