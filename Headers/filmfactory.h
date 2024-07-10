#ifndef OOP_FILMFACTORY_H
#define OOP_FILMFACTORY_H

#include "film.h"

class FilmFactory {
public:
    static Film createFilm(const std::string& nume, int durata, int pret, const std::vector<Actor>& cast, const std::vector<std::string>& schedule);
};

#endif // OOP_FILMFACTORY_H
