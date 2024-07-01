// film.h

#ifndef OOP_FILM_H
#define OOP_FILM_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

class Film {
private:
    std::string nume;
    int durata;
    int pret;
    std::vector<Actor> cast;
    std::vector<std::string> schedule; // Added schedule attribute
    std::vector<std::vector<char>> seating; // Seating arrangement

    void initializeSeating() {
        seating = std::vector<std::vector<char>>(5, std::vector<char>(10, 'O')); // 'O' for Occupied, 'L' for Free
        std::srand(std::time(nullptr)); // Seed for randomness
        for (auto& row : seating) {
            for (auto& seat : row) {
                if (std::rand() % 2 == 0) {
                    seat = 'L';
                }
            }
        }
    }

public:
    Film() = default;

    Film(const std::string& _nume, const int _durata, const int& _pret, const std::vector<Actor>& _cast, const std::vector<std::string>& _schedule)
            : nume(_nume), durata(_durata), pret(_pret), cast(_cast), schedule(_schedule) {
        initializeSeating();
    }

    Film& operator=(const Film& other) {
        if (this != &other) {
            nume = other.nume;
            durata = other.durata;
            pret = other.pret;
            cast = other.cast;
            schedule = other.schedule;
            seating = other.seating;
        }
        return *this;
    }

    Film(const Film& other)
            : nume(other.nume), durata(other.durata), pret(other.pret), cast(other.cast), schedule(other.schedule), seating(other.seating)
    {}

    ~Film() {}

    friend std::ostream& operator<<(std::ostream& os, const Film& other) {
        os << "Nume film: " << other.nume << ", Durata: " << other.durata << " minute, Pret: " << other.pret << " RON\n";
        os << "Actori: ";
        for (auto it = other.cast.begin(); it != other.cast.end(); ++it) {
            os << *it;
            if (it != other.cast.end() - 1) {
                os << ", ";
            }
        }
        os << "\n";
        return os;
    }

    int getPret() const {
        return pret;
    }

    void setPret(int newPret) {
        pret = newPret;
    }

    const std::string& getNume() const {
        return nume;
    }

    const std::vector<std::string>& getSchedule() const {
        return schedule;
    }

    void printFilmDetails() const {
        std::cout << "Nume film: " << nume << ", Durata: " << durata << " minute, Pret: " << pret << " RON\n";
        std::cout << "Actori: ";
        for (const auto& actor : cast) {
            std::cout << actor << "; ";
        }
        std::cout << "\n";
    }

    void printSeating() const {
        std::cout << "Legenda Loc (L: Liber, O: Ocupat):\n";
        for (size_t i = 0; i < seating.size(); ++i) {
            for (size_t j = 0; j < seating[i].size(); ++j) {
                std::cout << seating[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    bool isSeatFree(int row, int col) const {
        return seating[row][col] == 'L';
    }

    void occupySeat(int row, int col) {
        seating[row][col] = 'O';
    }
};

#endif // OOP_FILM_H
