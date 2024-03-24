#include <iostream>
#include <array>
#include <chrono>
//#include <thread>
//#include <SFML/Graphics.hpp>
//#include <Helper.h>
//#include "env_fixes.h"

class User{
private:
    std::string username;
    std::string parola;
public:
    User() = default;

    User(const std::string& _username, const std::string& _parola)
        :username(_username), parola(_parola)
    {}

    User& operator=(const User& other){
        username = other.username;
        parola = other.parola;
        return *this;
    }

    User(const User& other)
    {
        username = other.username;
        parola = other.parola;
    }

    ~User(){}

    friend std::ostream& operator<<(std::ostream& os, const User& other) {
        os << "Username: " << other.username << ", Parola: " << other.parola << "\n";
        return os;
    }
};

class Actor{
private:
    std::string nume;
    int varsta;
    std::vector<std::string> filmeJucate;
public:
    Actor() = default;

    Actor(const std::string& _nume, const int _varsta, const std::vector<std::string>& _filmeJucate)
            :nume(_nume), varsta(_varsta), filmeJucate(_filmeJucate)
    {}

    Actor& operator=(const Actor& other){
        nume = other.nume;
        varsta = other.varsta;
        filmeJucate = other.filmeJucate;
        return *this;
    }

    Actor(const Actor& other)
    {
        nume = other.nume;
        varsta = other.varsta;
    }

    ~Actor(){}

    friend std::ostream& operator<<(std::ostream& os, const Actor& other) {
        os << "Nume actor: " << other.nume << ", Varsta: " << other.varsta << "\n";
        os << "Filme jucate: ";
        for (const std::string& film : other.filmeJucate) {
            os << film << ", ";
        }
        os << "\n";
        return os;
    }
};

class Film{
private:
    std::string nume;
    int durata;
    std::vector<Actor> cast;
public:
    Film() = default;

    Film(const std::string& _nume, const int _durata, const std::vector<Actor>& _cast)
            :nume(_nume), durata(_durata), cast(_cast)
    {}

    Film& operator=(const Film& other){
        nume = other.nume;
        durata = other.durata;
        cast = other.cast;
        return *this;
    }

    Film(const Film& other)
    {
        nume = other.nume;
        durata = other.durata;
        cast = other.cast;
    }

    ~Film(){}

    friend std::ostream& operator<<(std::ostream& os, const Film& other) {
        os << "Nume film: " << other.nume << ", Durata: " << other.durata << "\n";
        os << "Actori: ";
        for (const std::string& actor : other.cast) {
            os << actor << ", ";
        }
        return os;
    }
};

int main() {

    Actor ac("Mihai", 12, {"Palm Angels", "Miron"});
    Actor ab;
    return 0;
}

