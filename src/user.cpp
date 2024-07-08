//
// Created by Gabriel on 7/8/2024.
//

#include "../Headers/user.h"

std::time_t User::addOneYear() const {
    std::time_t now = std::time(nullptr);
    struct tm expiryDate;

#ifdef _WIN32
    localtime_s(&expiryDate, &now);
#else
    localtime_r(&now, &expiryDate);
#endif

    expiryDate.tm_year += 1;
    return std::mktime(&expiryDate);
}

User::User() : categorie(false), isValidated(false), validationExpiry(0), role("user") {}

User::User(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta, const bool& _categorie, const std::string& _role)
        : username(_username), parola(_parola), salt(_salt), balanta(_balanta), categorie(_categorie), isValidated(false), validationExpiry(0), role(_role) {}

User& User::operator=(const User& other) {
    if (this != &other) {
        username = other.username;
        parola = other.parola;
        salt = other.salt;
        balanta = other.balanta;
        categorie = other.categorie;
        categoryType = other.categoryType;
        isValidated = other.isValidated;
        validationFileName = other.validationFileName;
        validationExpiry = other.validationExpiry;
        role = other.role;
    }
    return *this;
}

User::User(const User& other)
        : username(other.username), parola(other.parola), salt(other.salt), balanta(other.balanta), categorie(other.categorie),
          categoryType(other.categoryType), isValidated(other.isValidated), validationFileName(other.validationFileName), validationExpiry(other.validationExpiry), role(other.role) {}

User::~User() {}

std::ostream& operator<<(std::ostream& os, const User& other) {
    os << "Username: " << other.username << ", Parola: " << other.parola << "\n" << other.balanta;
    if (other.isValidated) {
        char buffer[80];
        struct tm * timeinfo = localtime(&other.validationExpiry);
        strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        os << ", Categorie: " << other.categoryType << ", Validat pana: " << buffer << "\n";
    }
    return os;
}

bool User::checkLogin(const std::string& _username, const std::string& _parola) const {
    std::string parolaHashed = PasswordManager::hash_password(_parola, salt);
    return (username == _username && parola == parolaHashed);
}

void User::setCategorie(bool categorieNoua) {
    categorie = categorieNoua;
}

void User::selectCategory() {
    if (isValidated) {
        char buffer[80];
        struct tm * timeinfo = localtime(&validationExpiry);
        strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        std::cout << "Deja esti validat ca " << categoryType << " cu o linceta valida " << buffer << ".\n";
        return;
    }

    std::cout << "Selectieaza categorie: [1] Student, [2] Pensionar\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        categoryType = "student";
    } else if (choice == 2) {
        categoryType = "pensioner";
    } else {
        std::cout << "Situatie invalida!\n";
        return;
    }

    std::cout << "Uploadeaza o poza cu un document care sa ateste categoria selectata (introdu numele fisierului, e.g., licenta.jpg): ";
    std::cin >> validationFileName;

    validateCategory();
}

void User::validateCategory() {
    isValidated = true;
    validationExpiry = addOneYear();
    std::cout << "Licenta " << categoryType << " a fost validata si este valabila un an din acest moment.\n";
}

int User::reducere(const Film& film) const {
    if (categorie && film.getPret() > 20) {
        std::cout << "Biletul a fost redus la 15 lei deoarece esti " << categoryType << ".\n";
        return 15;
    }
    return film.getPret();
}

int User::getBalanta() const {
    return balanta.getSuma();
}

Balanta& User::getBalantaObject() {
    return balanta;
}

void User::adaugaInBalanta(int sumaAdaugata) {
    if (sumaAdaugata < 10 || sumaAdaugata > 500) {
        throw CustomException("Suma adaugata trebuie sa fie intre 10 si 500.");
    } else {
        balanta.adaugaSuma(sumaAdaugata);
    }
}

bool User::areBani(int pretBilet) const {
    return balanta.getSuma() >= pretBilet;
}

void User::scadeDinBalanta(int sumaScazuta) {
    balanta.scadeSuma(sumaScazuta);
    std::cout << "Noua balanta: " << balanta.getSuma() << "\n";
}

std::string User::getRole() const {
    return role;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getParola() const {
    return parola;
}

const std::string& User::getSalt() const {
    return salt;
}

bool User::isCategorie() const {
    return categorie;
}
