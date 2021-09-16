#include "Ship.hpp"

Ship::Ship(sf::Vector2f pos, sf::Vector2f sp,
           sf::RenderWindow *win) {
    // phisics
    alive               = true;
    position            = pos;
    speed               = sp;
    rotation            = 0.f;
    // visualisation
    rotation_speed      = 5.f;
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