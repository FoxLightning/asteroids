#include "List.hpp"

List::List() {
    // create empty list
    count           = 0;
    current_element = NULL;
    first_element   = NULL;
    last_element    = NULL;
}

List::~List() {
    current_element = first_element;
    while (!DeleteCurrentElement()) {}
}

void List::AppendAsteroid(void *ptr) {
    Element *new_element      = new Element;
    new_element->data         = ptr;
    new_element->typeId       = ASTEROID;
    new_element->next_element = NULL;
    new_element->prev_element = NULL;
    if (count) {
        last_element->next_element = new_element;
        new_element->prev_element  = last_element;
        last_element               = new_element;
        count++;
    } else {
        count           = 1;
        first_element   = new_element;
        last_element    = new_element;
    }
}

void List::AppendBullet(void *ptr) {
    Element *new_element      = new Element;
    new_element->data         = ptr;
    new_element->typeId       = BULLET;
    new_element->next_element = NULL;
    new_element->prev_element = NULL;
    if (count) {
        last_element->next_element = new_element;
        new_element->prev_element  = last_element;
        last_element               = new_element;
        count++;
    } else {
        count           = 1;
        first_element   = new_element;
        last_element    = new_element;
    }
}

void *List::GetCurrentData() {
    return current_element->data;
}

int List::GetCurrentDataTypeId() {
    return current_element->typeId;
}

int List::DeleteCurrentElement() {
    Element *to_delete = current_element;

    if (!count) {
        std::cout << "ERROR empty list" << std::endl;
        return 1; 
    } else if (count == 1) {
        // delete element from list wich conteines only one element
        current_element = NULL;
        first_element = NULL;
        last_element = NULL;

    } else if (current_element->next_element == NULL) {
        // try to delete last element
        current_element->prev_element->next_element = NULL;
        current_element = current_element->prev_element;
        last_element = current_element;
    } else if (current_element->prev_element == NULL) {
        // try to delete first element
        current_element->next_element->prev_element = NULL;
        current_element = current_element->next_element;
        first_element = current_element;
    } else {
        current_element->next_element->prev_element = current_element->prev_element;
        current_element->prev_element->next_element = current_element->next_element;
    }

    count--;
    delete to_delete->data;
    delete to_delete;
    return 0;
}

int List::NextElement() {
    // return true if next element exitst and switch current to next element
    if (current_element->next_element == NULL) {
        return 1;
    } else {
        current_element = current_element->next_element;
        return 0;
    }

}

int List::GoToStart() {
    if (count == 0) {
        std::cout << "trying to set ptr on start of empty list" << std::endl;
        return 1;
    }
    current_element = first_element;
    return 0;

}

int List::GetCapacity() {
    return count;
}

void List::PrintInfo() {
    std::cout << "Capacity: " << count << std::endl;
    std::cout << "First: " << first_element << std::endl;
    std::cout << "Last: " << last_element << std::endl;
    std::cout << "Current: " << current_element << std::endl;
}
