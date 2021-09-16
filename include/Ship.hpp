#pragma once
#include <SFML/Graphics.hpp>

class Ship {
private:
    // phisics
    bool                alive;
    sf::Vector2f        position;
    sf::Vector2f        speed;
    sf::Vector2f        acceleration;
    long double         radious;
    // visualisation
    long double         rotation;
    long double         rotation_speed;
    long double         outline_thickness;
    sf::Color           fill_color;
    sf::Color           outline_color;
    sf::RenderWindow    *window;
    sf::ConvexShape     ConvexShape;

    void calculate();
public:
    Ship(sf::Vector2f pos, sf::Vector2f sp,
         sf::RenderWindow *win);
    ~Ship();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();
};