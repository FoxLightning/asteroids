#include <Asteroid.hpp>
#include <Ship.hpp>
#include <stdlib.h>
#include <cmath>

#include <iostream>

#define MARGIN              5
#define MAX_SPEED           10
#define MIN_SPEED           1
#define MAX_ROTATION_SPEED  2
#define MAX_RADIOUS         50
#define MIN_RADIOUS         10
#define MIN_DOTS_COUNT      7
#define MAX_DOTS_COUNT      10
#define PI                  3.14

// Asteroid::Asteroid(sf::Vector2f pos, sf::Vector2f sp,
//                    sf::RenderWindow *win, sf::Vector2i resolution) {
//     // phisics
//     borders             = resolution;
//     alive               = true;
//     position            = pos;
//     speed               = sp;
//     rotation            = 0.f;
//     // visualisation
//     rotation_speed      = 5.f;
//     radious             = 10000.f;

//     window              = win;
//     ConvexShape.setPointCount(5);
//     ConvexShape.setPoint(0, sf::Vector2f(0.f, -100.f));
//     ConvexShape.setPoint(1, sf::Vector2f(100.f, -50.f));
//     ConvexShape.setPoint(2, sf::Vector2f(70.f, 40.f));
//     ConvexShape.setPoint(3, sf::Vector2f(-60.f, 50.f));
//     ConvexShape.setPoint(4, sf::Vector2f(-40.f, -20.f));
//     ConvexShape.setFillColor(sf::Color::Transparent);
//     ConvexShape.setOutlineThickness(4.f);
//     ConvexShape.setOutlineColor(sf::Color::Blue);
//     ConvexShape.setPosition(position);
//     ConvexShape.setRotation(rotation);
// }

Asteroid::Asteroid(sf::RenderWindow *win, sf::Vector2i resolution, sf::Vector2f target) {
    std::cout << "Create asteroid " << this << std::endl;
    // const
    borders             = resolution;
    alive               = true;
    radious             = 100.f;
    window              = win;

    // srand(time(NULL));
    setRandomPosition();
    setRandomSpeed(target);
    rotation        = rand() % 360;
    rotation_speed  = rand() % MAX_ROTATION_SPEED;
    setShape();

    // the velocity vector must be directed towards the ship
    ConvexShape.setPointCount(dots_number);
    for (int i = 0; i < dots_number; i++) {
        std::cout << shape_dots[i].x << "  ";
        std::cout << shape_dots[i].y << std::endl;
        ConvexShape.setPoint(i, shape_dots[i]);
    }
    ConvexShape.setFillColor(sf::Color::Transparent);
    ConvexShape.setOutlineThickness(4.f);
    ConvexShape.setOutlineColor(sf::Color::Blue);
    ConvexShape.setPosition(position);
    ConvexShape.setRotation(rotation);

    // std::cout << "Asteroid randomly created with next parameters" << std::endl;
    // std::cout << "position x: " << position.x << std::endl;
    // std::cout << "position y: " << position.y << std::endl;
    // std::cout << "speed x: "    << speed.x << std::endl;
    // std::cout << "speed y: "    << speed.y << std::endl;
    std::cout << "############" << std::endl;
}
Asteroid::~Asteroid() {
    std::cout << "Delete asteroid " << this << std::endl;
    delete[] shape_dots;
}

void Asteroid::setRandomRadious() {
    radious = MAX_RADIOUS;
}

void Asteroid::setRandomDotsCount() {
    dots_number = rand() % MAX_DOTS_COUNT + MIN_DOTS_COUNT;
}

sf::Vector2f randomDot(float r, sf::Vector2f pos) {
    sf::Vector2f res;
    float min_x = pos.x - r;
    float max_x = pos.x + r;

    unsigned int mod_x = (unsigned int)((max_x - min_x) * 100);
    if (!mod_x) {
        mod_x = 1;
    }
    std::cout << "mod x " << mod_x << std::endl;

    res.x = (float)(rand() % mod_x) / 100.f + min_x;
    float min_y = pos.y - sqrt(r*r - (res.x - pos.x)*(res.x - pos.x));
    float max_y = pos.y + sqrt(r*r - (res.x - pos.x)*(res.x - pos.x));
    unsigned int mod_y = (unsigned int)((max_y - min_y) * 100);
    if (!mod_y) {
        mod_y = 1;
    }
    std::cout << "mod y " << mod_y << std::endl;

    res.y = (float)(rand() % mod_y) / 100.f + min_y;
    return res;
}

void Asteroid::setShape() {
    setRandomRadious();
    setRandomDotsCount();
    std::cout << dots_number << std::endl;
    shape_dots = new sf::Vector2f[dots_number];
    float r = radious * sin(PI / (float)dots_number);
    float step = 360.f/(float)dots_number;
    sf::Vector2f tmp;
    sf::Vector2f tmp_vec[dots_number];
    sf::Vector2f *tmpPtr = tmp_vec;
    for (float i=0; i<dots_number; i++, tmpPtr++) {
        tmp.x = (float)radious * sin(2*PI*i*step/360.f);
        tmp.y = (float)radious * cos(2*PI*i*step/360.f);
        *tmpPtr = tmp;
    }
    for (int i = 0; i < dots_number; i++) {
        shape_dots[i] = randomDot(r, tmp_vec[i]);
    }
}

int Asteroid::setRandomSpeed(sf::Vector2f target) {
    // Position must be set before using
    sf::Vector2f direction_vector;
    direction_vector.x = target.x - position.x;
    direction_vector.y = target.y - position.y;
    double direction = direction_vector.y / direction_vector.x;
    double mod_speed = 10;
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

void Asteroid::asteroid_die() {
    alive = false;
}

bool Asteroid::IsAlive() {
    return alive;
}

void Asteroid::draw() {
    calculate();
    if (alive) {
        ConvexShape.setPosition(position);
        ConvexShape.setRotation(rotation);
        window->draw(ConvexShape);
    }
}

Asteroid::Asteroid(const Asteroid &other) {
    this->outline_thickness = other.outline_thickness;
    this->fill_color = other.fill_color;
    this->outline_color = other.outline_color;
    this->window = other.window;
    this->ConvexShape = other.ConvexShape;

    this->borders = other.borders;
    this->alive = other.alive;
    this->position = other.position;
    this->speed = other.speed;
    this->acceleration = other.acceleration;
    this->radious = other.radious;
    this->rotation = other.rotation;

    this->rotation_speed = other.rotation_speed;
    this->dots_number = other.dots_number;

    this->shape_dots = new sf::Vector2f[other.dots_number];
    for (int i = 0; i < other.dots_number; i++) {
        this->shape_dots[i] = other.shape_dots[i];
    }
}
