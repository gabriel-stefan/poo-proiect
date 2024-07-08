#include "../Headers/film.h"

InvalidSeatException::InvalidSeatException(int row, int col)
        : CustomException("Pozitie a locului invalida (" + std::to_string(row) + ", " + std::to_string(col) + ").") {}

SeatAlreadyOccupiedException::SeatAlreadyOccupiedException(int row, int col)
        : CustomException("Locul este deja ocupat la pozitia (" + std::to_string(row) + ", " + std::to_string(col) + ").") {}

Film::Film() = default;

Film::Film(const std::string& _nume, const int _durata, const int& _pret, const std::vector<Actor>& _cast, const std::vector<std::string>& _schedule)
        : nume(_nume), durata(_durata), pret(_pret), cast(_cast), schedule(_schedule) {
    initializeSeating();
}

Film& Film::operator=(const Film& other) {
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

Film::Film(const Film& other)
        : nume(other.nume), durata(other.durata), pret(other.pret), cast(other.cast), schedule(other.schedule), seating(other.seating) {}

Film::~Film() = default;

std::ostream& operator<<(std::ostream& os, const Film& other) {
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

int Film::getPret() const {
    return pret;
}

void Film::setPret(int newPret) {
    pret = newPret;
}

const std::string& Film::getNume() const {
    return nume;
}

const std::vector<std::string>& Film::getSchedule() const {
    return schedule;
}

void Film::setSchedule(const std::vector<std::string>& newSchedule) {
    schedule = newSchedule;
}

void Film::printFilmDetails() const {
    std::cout << "Nume film: " << nume << ", Durata: " << durata << " minute, Pret: " << pret << " RON\n";
    std::cout << "Actori: ";
    for (const auto& actor : cast) {
        std::cout << actor << "; ";
    }
    std::cout << "\n";
}

void Film::printSeating() const {
    std::cout << "Legenda Loc (L: Liber, O: Ocupat):\n";
    for (size_t i = 0; i < seating.size(); ++i) {
        for (size_t j = 0; j < seating[i].size(); ++j) {
            std::cout << seating[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool Film::isSeatFree(int row, int col) const {
    if (row < 0 || row >= seating.size() || col < 0 || col >= seating[0].size()) {
        throw InvalidSeatException(row, col);
    }
    return seating[row][col] == 'L';
}

void Film::occupySeat(int row, int col) {
    if (row < 0 || row >= seating.size() || col < 0 || col >= seating[0].size()) {
        throw InvalidSeatException(row, col);
    }
    if (seating[row][col] == 'O') {
        throw SeatAlreadyOccupiedException(row, col);
    }
    seating[row][col] = 'O';
}

void Film::initializeSeating() {
    seating = std::vector<std::vector<char>>(5, std::vector<char>(10, 'O')); // 'O' for Occupied, 'L' for Free
    std::srand(std::time(nullptr));
    for (auto& row : seating) {
        for (auto& seat : row) {
            if (std::rand() % 2 == 0) {
                seat = 'L';
            }
        }
    }
}
