#pragma once
#include <Ship.hpp>

class Bullet :private AbstractPhysicalObject,
              public  AbstractPhysicalObjectInterface
{


public:
    bool IsAlive();
    void calculate();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();
    Bullet(Ship *ship);
    ~Bullet();
};