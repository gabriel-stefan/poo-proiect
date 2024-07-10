#ifndef FILM_FACTORY_H
#define FILM_FACTORY_H

#include "film.h"
#include <vector>
#include <string>

class FilmFactory {
public:
    static Film createActionFilm();
    static Film createComedyFilm();
    static Film createDramaFilm();
    static Film createFamilyFilm();
    static Film createThrillerFilm();
    static Film createSFFilm();
};

#endif // FILM_FACTORY_H
