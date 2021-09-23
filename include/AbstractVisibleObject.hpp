#pragma once

class AbstractVisibleObject {
protected:
    long double         outline_thickness;
    sf::Color           fill_color;
    sf::Color           outline_color;
    sf::RenderWindow    *window;
    sf::ConvexShape     ConvexShape;
public:
    virtual void draw() = 0;
    AbstractVisibleObject();
    ~AbstractVisibleObject();
};
