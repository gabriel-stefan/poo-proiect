#ifndef OOP_ADMIN_H
#define OOP_ADMIN_H

#include "user.h"
#include "film.h"
#include <vector>

class Admin : public User {
public:
    Admin(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta);

    void adaugaFilm(std::vector<Film>& filme, const Film& filmNou);

    void modificaPretFilm(Film& film, int pretNou);

    void modificaProgramFilm(Film& film, const std::vector<std::string>& programNou);
};

#endif // OOP_ADMIN_H