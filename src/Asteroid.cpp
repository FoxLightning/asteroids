#include <Asteroid.hpp>
#include <Ship.hpp>
#include <stdlib.h>
#include <cmath>

#include <iostream>

#define MARGIN              5
#define MAX_SPEED           10
#define MIN_SPEED           1
#define MAX_ROTATION_SPEED  10

Asteroid::Asteroid(sf::Vector2f pos, sf::Vector2f sp,
                   sf::RenderWindow *win, sf::Vector2i resolution) {
    // phisics
    borders             = resolution;
    alive               = true;
    position            = pos;
    speed               = sp;
    rotation            = 0.f;
    // visualisation
    rotation_speed      = 5.f;
    radious             = 100.f;

    window              = win;
    ConvexShape.setPointCount(5);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -100.f));
    ConvexShape.setPoint(1, sf::Vector2f(100.f, -50.f));
    ConvexShape.setPoint(2, sf::Vector2f(70.f, 40.f));
    ConvexShape.setPoint(3, sf::Vector2f(-60.f, 50.f));
    ConvexShape.setPoint(4, sf::Vector2f(-40.f, -20.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);
}

Asteroid::Asteroid(sf::RenderWindow *win, sf::Vector2i resolution, sf::Vector2f target) {
    // const
    borders             = resolution;
    alive               = true;
    radious             = 100.f;
    window              = win;

    srand(time(NULL));
    setRandomPosition();
    setRandomSpeed(target);
    rotation        = rand() % 360;
    rotation_speed  = rand() % MAX_ROTATION_SPEED;


    // the velocity vector must be directed towards the ship
    ConvexShape.setPointCount(5);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -100.f));
    ConvexShape.setPoint(1, sf::Vector2f(100.f, -50.f));
    ConvexShape.setPoint(2, sf::Vector2f(70.f, 40.f));
    ConvexShape.setPoint(3, sf::Vector2f(-60.f, 50.f));
    ConvexShape.setPoint(4, sf::Vector2f(-40.f, -20.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);

    std::cout << "position x: " << position.x << std::endl;
    std::cout << "position y: " << position.y << std::endl;
    std::cout << "speed x: "    << speed.x << std::endl;
    std::cout << "speed y: "    << speed.y << std::endl;
}

Asteroid::~Asteroid() {
}

int Asteroid::setRandomSpeed(sf::Vector2f target) {
    // Position must be set before using
    sf::Vector2f direction_vector;
    direction_vector.x = target.x - position.x;
    direction_vector.y = target.y - position.y;
    double direction = direction_vector.y / direction_vector.x;
    double mod_speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED);
    speed.x = mod_speed / (sqrt(1 + direction * direction));
    speed.y = speed.x * direction;
    if (direction_vector.x < 0) {
        speed.x *= -1.f;
        speed.y *= -1.f;
    }
    return 0;
}

int Asteroid::setRandomPosition() {
    if (borders.x < MARGIN*4 || borders.y < MARGIN*4) {
        return 1;
    }
    // genberate random position (it should be near the edges of the screen )
    // choose a edge of the screen 
    switch (rand()%4)
    {
    case 0:
        // top edge
        position = sf::Vector2f(MARGIN+rand()%(borders.x-MARGIN), MARGIN);
        break;
    case 1:
        // down edge
        position = sf::Vector2f(MARGIN+rand()%(borders.x-MARGIN), borders.y-MARGIN);
        break;
    case 2:
        // right edge
        position = sf::Vector2f(borders.x-MARGIN, MARGIN+rand()%(borders.y-MARGIN));
        break;
    default:
        // left edge
        position = sf::Vector2f(MARGIN, MARGIN+rand()%(borders.y-MARGIN));
        break;
    }
    return 0;
}

void Asteroid::calculate() {
    position.x  += speed.x;
    position.y  += speed.y;
    rotation    += rotation_speed;
    if (position.x > borders.x) {
        position.x = (int)position.x % borders.x;
    }
    if (position.y > borders.y) {
        position.y = (int)position.y % borders.y;
    }
    if (position.x < 0) {
        position.x = position.x+borders.x;
    }
    if (position.y < 0) {
        position.y = position.y+borders.y;
    }
}

sf::Vector2f Asteroid::GetPosition() {
    return position;
}

long double Asteroid::GetRadious() {
    return radious;
}

void Asteroid::draw() {
    calculate();
    if (alive) {
        ConvexShape.setPosition(position);
        ConvexShape.setRotation(rotation);
        window->draw(ConvexShape);
    }
}
