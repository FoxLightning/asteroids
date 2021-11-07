#include "Bullet.hpp"
#include <Ship.hpp>
#include <cmath>
#include <stdlib.h>
#include <CommonConst.hpp>

#define BULLET_SPEED 20.f


Bullet::Bullet(Ship *ship) {
    position    = ship->position;
    speed       = ship->speed;
    borders     = ship->borders;
    rotation    = ship->rotation;
    window      = ship->window;
    alive       = true;
    radious     = 10.f;

    setSpeed(ship);
    setRecoil(ship);
    setShape();
}

void Bullet::setSpeed(Ship *ship) {
    double accuracy = (399.f - rand() % 800) / 100.f;
    speed.x = ship->speed.x + cos((rotation-90+accuracy)*PI/180.0)*BULLET_SPEED;
    speed.y = ship->speed.y + sin((rotation-90+accuracy)*PI/180.0)*BULLET_SPEED;
}

void Bullet::setShape() {
    ConvexShape.setPointCount(3);
    ConvexShape.setPoint(0, sf::Vector2f(0.f, -1.f));
    ConvexShape.setPoint(1, sf::Vector2f(-1.f, 0.f));
    ConvexShape.setPoint(2, sf::Vector2f(1.f, 0.f));
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);
}

void Bullet::setRecoil(Ship *ship) {
    ship->speed.x -= speed.x / 400.f;
    ship->speed.y -= speed.y / 400.f;
}

Bullet::~Bullet() {}

void Bullet::calculate() {
    position.x  += speed.x;
    position.y  += speed.y;
    if (position.x > borders.x ||
        position.x < 0 ||
        position.y > borders.y ||
        position.y < 0) {
        alive = false;
    }
}

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
