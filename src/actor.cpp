#include "../Headers/actor.h"

// Default constructor
Actor::Actor() = default;

// Parameterized constructor
Actor::Actor(const std::string& _nume, const int _varsta)
        : nume(_nume), varsta(_varsta)
{}

// Copy assignment operator
Actor& Actor::operator=(const Actor& other) {
    if (this != &other) {
        nume = other.nume;
        varsta = other.varsta;
    }
    return *this;
}

// Copy constructor
Actor::Actor(const Actor& other)
        : nume(other.nume), varsta(other.varsta)
{}

// Destructor
Actor::~Actor() = default;

// Overloaded << operator
std::ostream& operator<<(std::ostream& os, const Actor& other) {
    os << other.nume << ", " << other.varsta << " ani ";
    return os;
}
