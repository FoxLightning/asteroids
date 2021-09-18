#pragma once
#include <SFML/Graphics.hpp>

class AbstractPhysicalObject {
public:
    // phisics
    sf::Vector2i        borders;
    bool                alive;
    sf::Vector2f        position;
    sf::Vector2f        speed;
    sf::Vector2f        acceleration;
    long double         radious;
    // visualisation
    long double         rotation;
    long double         outline_thickness;
    sf::Color           fill_color;
    sf::Color           outline_color;
    sf::RenderWindow    *window;
    sf::ConvexShape     ConvexShape;
};


class AbstractPhysicalObjectInterface {
public:
    virtual void calculate() = 0;
    virtual sf::Vector2f GetPosition() = 0;
    virtual long double GetRadious() = 0;
    virtual void draw() = 0;
};
