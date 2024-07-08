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
    Actor();
    Actor(const std::string& _nume, const int _varsta);
    Actor& operator=(const Actor& other);
    Actor(const Actor& other);
    ~Actor();

    friend std::ostream& operator<<(std::ostream& os, const Actor& other);
};

#endif //OOP_ACTOR_H
