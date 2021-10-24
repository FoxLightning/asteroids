#pragma once
#include <SFML/Graphics.hpp>
#include <AbstractPhysicalObject.hpp>
#include <AbstractVisibleObject.hpp>


class Asteroid: public AbstractPhysicalObject,
                public AbstractVisibleObject
{
private:
    long double         rotation_speed;
    int                 dots_number;
    sf::Vector2f        *shape_dots;

    // methods for random generation
    int setRandomPosition();
    int setRandomSpeed(sf::Vector2f target);
    void setRandomRadious();
    void setRandomDotsCount();
    void setRandomDots();
    void setRandomShape();
    void setRandomRotationSpeed();
    void setConvexShape();
public:
    Asteroid(sf::Vector2f pos, sf::Vector2f sp,
             sf::RenderWindow *win, sf::Vector2i resolution);
    Asteroid(sf::RenderWindow *win, sf::Vector2i resolution,
             sf::Vector2f target);
    ~Asteroid();

    void calculate();
    void draw();
    long double GetRadious();
    sf::Vector2f GetPosition();
    bool IsAlive();
    void asteroid_die();

    Asteroid(const Asteroid &asteroid);
};
