#include <Ship.hpp>
#include <math.h>
#include <commonConst.hpp>

#define ENGINE_BOOST 0.02


Ship::Ship(sf::Vector2f pos, sf::Vector2f sp,
           sf::RenderWindow *win, sf::Vector2i resolution) {
    // phisics
    borders             = resolution;
    window              = win;
    position            = pos;
    speed               = sp;
    alive               = true;
    rotation            = 0.f;
    radious             = 10.f;
    mass                = 200.f;

    setShape();
}

Ship::~Ship() {}

void Ship::setShape() {
    ConvexShape.setPointCount(3);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -10.f));
    ConvexShape.setPoint(1, sf::Vector2f(-5.f, 10.f));
    ConvexShape.setPoint(2, sf::Vector2f(5.f, 10.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
}

void Ship::calculate() {
    speed.x     += acceleration.x;
    speed.y     += acceleration.y;
    position.x  += speed.x;
    position.y  += speed.y;
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

long double Ship::GetRadious() {
    return radious;
}

void Ship::draw() {
    calculate();
    if (alive) {
        ConvexShape.setPosition(position);
        ConvexShape.setRotation(rotation);
        window->draw(ConvexShape);
    }
}

void Ship::SetRotation(long double input_rotation) {
    rotation = input_rotation;
}

void Ship::engine_on() {
    acceleration.x = ENGINE_BOOST * cos((rotation-90) * PI / 180.f);
    acceleration.y = ENGINE_BOOST * sin((rotation-90) * PI / 180.f);;
}

void Ship::engine_off() {
    acceleration.x = 0;
    acceleration.y = 0;
}
