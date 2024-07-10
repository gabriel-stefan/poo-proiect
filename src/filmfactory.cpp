#include "../Headers/filmfactory.h"

Film FilmFactory::createActionFilm() {
    std::vector<Actor> cast = {Actor("Star de Actiune", 35), Actor("Actor Secundar", 40)};
    std::vector<std::string> schedule = {"2024-07-01 18:00", "2024-07-02 18:00", "2024-07-03 18:00"};
    return Film("Film de Actiune", 120, 25, cast, schedule);
}

Film FilmFactory::createComedyFilm() {
    std::vector<Actor> cast = {Actor("Star de Comedie", 30), Actor("Partener Amuzant", 28)};
    std::vector<std::string> schedule = {"2024-07-04 20:00", "2024-07-05 20:00", "2024-07-06 20:00"};
    return Film("Film de Comedie", 90, 20, cast, schedule);
}

Film FilmFactory::createDramaFilm() {
    std::vector<Actor> cast = {Actor("Star de Drama", 45), Actor("Actor Secundar", 50)};
    std::vector<std::string> schedule = {"2024-07-07 19:00", "2024-07-08 19:00", "2024-07-09 19:00"};
    return Film("Film de Drama", 140, 30, cast, schedule);
}

Film FilmFactory::createFamilyFilm() {
    std::vector<Actor> cast = {Actor("Star de Familie", 32), Actor("Actor Tanar", 18)};
    std::vector<std::string> schedule = {"2024-07-10 17:00", "2024-07-11 17:00", "2024-07-12 17:00"};
    return Film("Film de Familie", 100, 18, cast, schedule);
}

Film FilmFactory::createThrillerFilm() {
    std::vector<Actor> cast = {Actor("Star de Thriller", 38), Actor("Actor Misterios", 42)};
    std::vector<std::string> schedule = {"2024-07-13 21:00", "2024-07-14 21:00", "2024-07-15 21:00"};
    return Film("Film de Thriller", 110, 22, cast, schedule);
}

Film FilmFactory::createSFFilm() {
    std::vector<Actor> cast = {Actor("Star de SF", 40), Actor("Actor Secundar", 35)};
    std::vector<std::string> schedule = {"2024-07-16 20:00", "2024-07-17 20:00", "2024-07-18 20:00"};
    return Film("Film SF", 130, 28, cast, schedule);
}

