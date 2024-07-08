#ifndef OOP_ADMIN_H
#define OOP_ADMIN_H

#include "user.h"
#include "film.h"
#include <vector>

class Admin : public User {
public:
    Admin(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta)
            : User(_username, _parola, _salt, _balanta, false, "admin") {}

    void adaugaFilm(std::vector<Film>& filme, const Film& filmNou) {
        filme.push_back(filmNou);
        std::cout << "Film adaugat cu succes!\n";
    }

    void modificaPretFilm(Film& film, int pretNou) {
        film.setPret(pretNou);
        std::cout << "Pretul filmului a fost modificat cu succes!\n";
    }

    void modificaProgramFilm(Film& film, const std::vector<std::string>& programNou) {
        film.setSchedule(programNou);
        std::cout << "Programul filmului a fost modificat cu succes!\n";
    }
};

#endif // OOP_ADMIN_H
