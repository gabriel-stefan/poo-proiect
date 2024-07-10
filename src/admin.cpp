#include "../Headers/admin.h"
#include <iostream>

Admin::Admin(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta)
        : User(_username, _parola, _salt, _balanta, false, "admin") {}

void Admin::adaugaFilm(std::vector<Film>& filme, const Film& filmNou) {
    filme.push_back(filmNou);
    std::cout << "Film adaugat cu succes!\n";
}

void Admin::modificaPretFilm(Film& film, int pretNou) {
    film.setPret(pretNou);
    std::cout << "Pretul filmului a fost modificat cu succes!\n";
}

void Admin::modificaProgramFilm(Film& film, const std::vector<std::string>& programNou) {
    film.setSchedule(programNou);
    std::cout << "Programul filmului a fost modificat cu succes!\n";
}