#include "Ship.hpp"
#include <math.h>
#include <iostream>
#define PI 3.14159265
#define SCREEN_X  1280
#define SCREEN_Y  720

Ship::Ship(sf::Vector2f pos, sf::Vector2f sp,
           sf::RenderWindow *win) {
    // phisics
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
    if (position.x > SCREEN_X) {
        position.x = (int)position.x % SCREEN_X;
    }
    if (position.y > SCREEN_Y) {
        position.y = (int)position.y % SCREEN_Y;
    }
    if (position.x < 0) {
        position.x = position.x+SCREEN_X;
    }
    if (position.y < 0) {
        position.y = position.y+SCREEN_Y;
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

void Ship::turn_left() {
    rotation -= 10;
    if (rotation < 360) {
        rotation += 360;
    }
}

void Ship::turn_right() {
    rotation += 10;
    if (rotation > 360) {
        rotation -= 360;
    }
}

void Ship::engine_on() {
    acceleration.x = 0.1 * cos((rotation-90) * PI / 180.f);
    acceleration.y = 0.1 * sin((rotation-90) * PI / 180.f);;
}

void Ship::engine_off() {
    acceleration.x = 0;
    acceleration.y = 0;
}

void fire() {
    std::cout << "Пиу" << std::endl;
}
