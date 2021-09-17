#include <Asteroid.hpp>
#define SCREEN_X  1280
#define SCREEN_Y  720

Asteroid::Asteroid(sf::Vector2f pos, sf::Vector2f sp,
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

Asteroid::~Asteroid() {
}

void Asteroid::calculate() {
    position.x  += speed.x;
    position.y  += speed.y;
    rotation    += rotation_speed;
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
