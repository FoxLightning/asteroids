#pragma once
#include <SFML/Graphics.hpp>

class Asteroid {
private:
    // phisics
    bool                alive;
    sf::Vector2f        position;
    sf::Vector2f        speed;
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
    Asteroid(sf::Vector2f pos, sf::Vector2f sp,
             sf::RenderWindow *win);
    ~Asteroid();
    sf::Vector2f GetPosition();
    long double GetRadious();
    void draw();

};