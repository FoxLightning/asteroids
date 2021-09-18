#pragma once
#include <Asteroid.hpp>
#include <iostream>

enum TypeId
{
    ASTEROID = 0,
    BULLET
};

struct Element {
    int     typeId;
    void    *data;
    Element *next_element;
    Element *prev_element;
};

class List {
    unsigned int count;
    Element *current_element;
    Element *first_element;
    Element *last_element;

public:
    void AppendAsteroid(void *ptr);
    void AppendBullet(void *ptr);

    void *GetCurrentData();
    int GetCurrentDataTypeId();
    int DeleteCurrentElement();

    int NextElement();
    int GoToStart();
    int GetCapacity();
    void PrintInfo();

    List();
    ~List();
};