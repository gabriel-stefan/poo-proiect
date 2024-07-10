#ifndef OOP_FILM_H
#define OOP_FILM_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "exceptieCustom.h"
#include "actor.h"

class InvalidSeatException : public CustomException {
public:
    InvalidSeatException(int row, int col);
};

class SeatAlreadyOccupiedException : public CustomException {
public:
    SeatAlreadyOccupiedException(int row, int col);
};

class Film {
private:
    std::string nume;
    int durata;
    int pret;
    std::vector<Actor> cast;
    std::vector<std::string> schedule;
    std::vector<std::vector<char>> seating;

    void initializeSeating();

public:
    Film();
    Film(const std::string& _nume, const int _durata, const int& _pret, const std::vector<Actor>& _cast, const std::vector<std::string>& _schedule);
    Film& operator=(const Film& other);
    Film(const Film& other);
    ~Film();

    friend std::ostream& operator<<(std::ostream& os, const Film& other);

    int getPret() const;
    void setPret(int newPret);
    const std::string& getNume() const;
    const std::vector<std::string>& getSchedule() const;
    void setSchedule(const std::vector<std::string>& newSchedule);

    void printFilmDetails() const;
    void printSeating() const;
    bool isSeatFree(int row, int col) const;
    void occupySeat(int row, int col);
};

#endif // OOP_FILM_H