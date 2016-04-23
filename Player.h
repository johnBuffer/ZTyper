#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity2D.h"
#include "Zombie.h"

class Player : public Entity2D
{
public:
    Player(double x, double y);
    void setTarget(Zombie* z) {_target = z;};

    double getScore() const {return _score;}
    double getCombo() const {return _combo;}
    int getAccuracy() const {return _accuracy*100;}
    double getAngle() const {return _angle;}
    double getTargetDist() const {return _targetDist;}
    double getRecoil() const {return _recoil;}
    Zombie* getTarget() const {return _target;}

    bool shoot(char c);
    void update();

private:
    Zombie* _target;
    double _score, _combo, _accuracy, _hit, _total;
    double _angle, _targetDist, _recoil;

};

#endif // PLAYER_H_INCLUDED
