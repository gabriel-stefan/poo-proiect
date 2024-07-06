//
// Created by Gabriel on 7/7/2024.
//

#ifndef OOP_ACTOR_H
#define OOP_ACTOR_H

#include <iostream>
#include <string>

class Actor {
private:
    std::string nume;
    int varsta;
public:
    Actor() = default;

    Actor(const std::string& _nume, const int _varsta)
            : nume(_nume), varsta(_varsta)
    {}

    Actor& operator=(const Actor& other) {
        if (this != &other) {
            nume = other.nume;
            varsta = other.varsta;
        }
        return *this;
    }

    Actor(const Actor& other)
            : nume(other.nume), varsta(other.varsta)
    {}

    ~Actor() {}

    friend std::ostream& operator<<(std::ostream& os, const Actor& other) {
        os << other.nume << ", " << other.varsta << " ani ";
        return os;
    }
};

#endif //OOP_ACTOR_H
