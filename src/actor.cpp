#include "../Headers/actor.h"

Actor::Actor() = default;

Actor::Actor(const std::string& _nume, const int _varsta)
        : nume(_nume), varsta(_varsta)
{}

Actor& Actor::operator=(const Actor& other) {
    if (this != &other) {
        nume = other.nume;
        varsta = other.varsta;
    }
    return *this;
}

Actor::Actor(const Actor& other)
        : nume(other.nume), varsta(other.varsta)
{}

Actor::~Actor() = default;

std::ostream& operator<<(std::ostream& os, const Actor& other) {
    os << other.nume << ", " << other.varsta << " ani ";
    return os;
}
