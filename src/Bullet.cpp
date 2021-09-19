#include "Bullet.hpp"
#include <Ship.hpp>
#include <cmath>
#include <iostream>

#define BULLET_SPEED 20.f
#define PI 3.14159265

Bullet::Bullet(Ship *ship) {
    alive = true;
    position = ship->position;
    speed = ship->speed;
    borders = ship->borders;
    radious = 1.f;
    rotation = ship->rotation;
    speed.x += cos((rotation-90)*PI/180.0)*BULLET_SPEED;
    speed.y += sin((rotation-90)*PI/180.0)*BULLET_SPEED;

    window = ship->window;
    ConvexShape.setPointCount(3);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -10.f));
    ConvexShape.setPoint(1, sf::Vector2f(-1.f, 10.f));
    ConvexShape.setPoint(2, sf::Vector2f(1.f, 10.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);
    std::cout << "Crated bullet" << std::endl;
    std::cout << "position x: " << position.x << std::endl;
    std::cout << "position y: " << position.y << std::endl;
    std::cout << "speed x: " << speed.x << std::endl;
    std::cout << "speed y: " << speed.y << std::endl;
    std::cout << "Crated bullet" << std::endl;
    std::cout << "Crated bullet" << std::endl;
}

Bullet::~Bullet() {

}

void Bullet::calculate() {
    position.x  += speed.x;
    position.y  += speed.y;
    if (position.x > borders.x ||
        position.x < 0 ||
        position.y > borders.y ||
        position.y < 0) {
        std::cout << "bullet should be delete " << std::endl;
        alive = false;
    }
}
sf::Vector2f Bullet::GetPosition() {
    return position;
};
long double Bullet::GetRadious() {
    return radious;
}
bool Bullet::IsAlive() {
    return alive;
}

void Bullet::draw() {
    calculate();
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);
    window->draw(ConvexShape);
}