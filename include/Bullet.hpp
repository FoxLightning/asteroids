#pragma once
#include <Ship.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>


class Bullet: public AbstractPhysicalObject,
              public AbstractVisibleObject
{
private:
    void setSpeed(Ship *ship);
    void setRecoil(Ship *ship);
    void setShape();
public:
    bool IsAlive();
    void calculate();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();
    Bullet(Ship *ship);
    ~Bullet();
};
