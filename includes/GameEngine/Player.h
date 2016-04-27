#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity2D.h"
#include <list>
#include "Zombie.h"

struct FireExplosion
{
    FireExplosion(sf::Sprite sprite, double speed);
    int getRank() const {return _sheetRank;}
    sf::Sprite _sprite;
    double _sheetRank, _speed;
};

class Player : public Entity2D
{
public:
    Player(double x, double y);

    int     getAccuracy() const {return _accuracy*100;}
    int     getExplosionRank() const {return _explosionRank;}
    double  getScore() const {return _score;}
    double  getCombo() const {return _combo;}
    double  getAngle() const {return _angle;}
    double  getTargetDist() const {return _targetDist;}
    double  getRecoil() const {return _recoil;}
    bool    shoot(char c);
    bool    isTargetLocked() const {return _targetLocked;}
    Zombie* getTarget() const {return _target;}

    void    setTarget(Zombie* z) {_target = z;};
    void    onContact(Entity2D*);
    void    update();

    void draw(sf::RenderTarget* renderer, sf::RenderTarget* bloom);

private:
    Zombie*   _target;
    double    _score, _combo, _accuracy, _hit, _total;
    double    _angle, _targetDist, _recoil, _explosionRank;
    double    _sightRadius, _sightX, _sightY, _sightAngle;
    sf::Clock _sightClock;
    bool      _targetLocked;

    std::list<FireExplosion> _explosions;
};

#endif // PLAYER_H_INCLUDED
