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
    long double         radious;
    long double         rotation;
public:
    virtual void calculate() = 0;
    virtual sf::Vector2f GetPosition() = 0;
    virtual long double GetRadious() = 0;
    AbstractPhysicalObject();
    ~AbstractPhysicalObject();
};
