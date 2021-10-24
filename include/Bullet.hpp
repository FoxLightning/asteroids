#pragma once
#include <Ship.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>


class Bullet: public AbstractPhysicalObject,
              public AbstractVisibleObject
{
public:
    bool IsAlive();
    void calculate();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();
    Bullet(void *ship);
    ~Bullet();
};
