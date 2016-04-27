#include "../../includes/GameEngine/Player.h"

#include <cmath>

FireExplosion::FireExplosion(sf::Sprite sprite, double speed):
    _sprite(sprite),
    _sheetRank(0),
    _speed(speed)
{
}

Player::Player(double x, double y) :
    Entity2D(x, y, 30),
    _lifes(3),
    _target(NULL),
    _angle(-3.14159/2.0)
{
    _score = 0;
    _combo = 0;
    _accuracy = 0;
    _hit = 0;
    _total = 0;
    _recoil = 0;
    _static = true;
    _targetLocked = true;
    _explosionRank = 19;
}

bool Player::shoot(char c)
{
    bool hit = false;
    if (!_target)
        return hit;

    hit = _target->shootNextLetter(c);

    if (hit)
    {
        _combo++;
        _score++;
        _hit++;
        _recoil = 20;
        _explosionRank = -1;

        const auto& texFire = ResourceManager<Sprite>::instance().get("explosion")->tex();
        sf::Sprite fire(*texFire);
        fire.setTextureRect(sf::IntRect(0, 0, 50, 128));
        fire.setOrigin(26, 125);

        fire.setPosition(_x+60*cos(_angle), _y+60*sin(_angle));
        fire.setRotation(_angle*57.2958+90);
        fire.setScale(0.9, 0.9);
        _explosions.push_back(FireExplosion(fire, 1));

        fire.setPosition(_x+80*cos(_angle), _y+80*sin(_angle));
        fire.setScale(0.25, 0.25);
        fire.setRotation(_angle*57.2958);
        _explosions.push_back(FireExplosion(fire, 0.5));

        fire.setRotation(_angle*57.2958+180);
        _explosions.push_back(FireExplosion(fire, 0.5));
    }
    else
    {
        _combo = 0;
    }
    _total++;

    _accuracy = (_hit+1)/(_total+1.0);

    return hit;
}

void Player::onContact(Entity2D* e)
{
    _lifes--;
    static_cast<Zombie*>(e)->kill();
}

void Player::update()
{
    for (auto& expl : _explosions)
        expl._sheetRank+=expl._speed;

    _explosions.remove_if([](FireExplosion& e) {return e._sheetRank==20;});

    /*if (_explosionRank < 19)
        _explosionRank+=1;*/

    _recoil += -_recoil/2.0;
    _targetLocked = true;

    if (!_target)
        return;

    if (!_target->getLife())
    {
        _target = NULL;
        return;
    }

    double vx = _target->getX()-_x;
    double vy = _target->getY()-_y;

    _targetDist = sqrt(vx*vx+vy*vy);

    double a = acos(vx/_targetDist);
    if (vy < 0) a *= -1;

    _angle += (a - _angle)/4.0;
    _targetLocked = std::abs(_angle-a) < 0.05;
}

void Player::draw(sf::RenderTarget* renderer, sf::RenderTarget* bloom)
{
    const auto& texTurret = ResourceManager<Sprite>::instance().get("turret")->tex();
    const auto& texBase = ResourceManager<Sprite>::instance().get("base")->tex();
    const auto& texFire = ResourceManager<Sprite>::instance().get("explosion")->tex();

    sf::Sprite base(*texBase);
    base.setOrigin(65, 72);
    base.setScale(0.65, 0.65);
    base.setPosition(_x, _y);

    sf::Sprite turret(*texTurret);
    turret.setOrigin(78, 245);
    turret.setScale(0.35, 0.35);
    turret.setPosition(_x-_recoil*cos(_angle), _y-_recoil*sin(_angle));
    turret.setRotation(_angle*57.2958+90);

    /*int explosionRank = _explosionRank;
    sf::Sprite fire(*texFire);
    fire.setTextureRect(sf::IntRect(50*explosionRank, 0, 50, 128));
    fire.setOrigin(26, 125);
    fire.setPosition(_x+60*cos(_angle), _y+60*sin(_angle));
    fire.setRotation(_angle*57.2958+90);
    fire.setScale(0.9, 0.9);*/

    for (auto& expl : _explosions)
    {
        expl._sprite.setTextureRect(sf::IntRect(50*expl.getRank(), 0, 50, 128));
        renderer->draw(expl._sprite);
        if (expl._sheetRank < 7)
        {
            expl._sprite.scale(1.1, 1.1);
            bloom->draw(expl._sprite);
            expl._sprite.scale(10/11., 10/11.);
        }
    }

    if (_target)
    {
        double rTarget = _target->getR()+10;
        sf::Vector2f posTarget(_target->getX(), _target->getY());
        sf::CircleShape targetShape(rTarget);
        targetShape.setOrigin(rTarget, rTarget);
        targetShape.setPosition(posTarget);
        targetShape.setFillColor(sf::Color::Green);
        renderer->draw(targetShape);

        sf::VertexArray laser(sf::Lines, 2);
        laser[0].position = sf::Vector2f(_x, _y);
        laser[0].color = sf::Color::Red;
        laser[1].position = sf::Vector2f(_x+_targetDist*cos(_angle), _y+_targetDist*sin(_angle));
        laser[1].color= sf::Color(255, 0, 0, 0);

        renderer->draw(laser);
    }

    renderer->draw(base);
    renderer->draw(turret);
}
