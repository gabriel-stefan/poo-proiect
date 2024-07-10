#include "../Headers/filmfactory.h"

Film FilmFactory::createFilm(const std::string& nume, int durata, int pret, const std::vector<Actor>& cast, const std::vector<std::string>& schedule) {
    return Film(nume, durata, pret, cast, schedule);
}
