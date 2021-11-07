#pragma once
#include <SFML/Graphics.hpp>


class AbstractPhysicalObject {
protected:
    // phisics
    sf::Vector2i        borders;
    bool                alive;
    sf::Vector2f        position;
    sf::Vector2f        speed;
    sf::Vector2f        acceleration;
    int                 radious;
    long double         rotation;
public:
    virtual void            calculate() =0;
    sf::Vector2f            GetPosition() {return position;};
    sf::Vector2f            GetSpeed() {return speed;};
    void                    SetSpeed(sf::Vector2f in_speed) {speed = in_speed;}
    virtual long double     GetRadious() =0;
    AbstractPhysicalObject() {};
    virtual                 ~AbstractPhysicalObject() {};
};
