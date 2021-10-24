#include <Ship.hpp>
#include <math.h>
#include <CommonConst.hpp>


Ship::Ship(sf::Vector2f pos, sf::Vector2f sp,
           sf::RenderWindow *win, sf::Vector2i resolution) {
    // phisics
    borders             = resolution;
    alive               = true;
    position            = pos;
    speed               = sp;
    rotation            = 0.f;
    // visualisation
    radious             = 100.f;

    window              = win;
    ConvexShape.setPointCount(3);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -10.f));
    ConvexShape.setPoint(1, sf::Vector2f(-5.f, 10.f));
    ConvexShape.setPoint(2, sf::Vector2f(5.f, 10.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);
}

Ship::~Ship() {

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

sf::Vector2f Ship::GetPosition() {
    return position;
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
    acceleration.x = 0.1 * cos((rotation-90) * PI / 180.f);
    acceleration.y = 0.1 * sin((rotation-90) * PI / 180.f);;
}

void Ship::engine_off() {
    acceleration.x = 0;
    acceleration.y = 0;
}

void Ship::AddSpeed(sf::Vector2f inp_speed) {
    speed.x -= (inp_speed.x / 200);
    speed.y -= (inp_speed.y / 200);
}
