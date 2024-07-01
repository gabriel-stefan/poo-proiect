// user.h

#ifndef OOP_USER_H
#define OOP_USER_H

#include <string>
#include <iostream>
#include <ctime>
#include "film.h"
#include "passwordmanager.h"
#include <vector>
#include "balanta.h"

class InvalidBalanceOperationException : public std::runtime_error {
public:
    InvalidBalanceOperationException(const std::string &message)
            : std::runtime_error(message) {}
};

class User {
private:
    std::string username;
    std::string parola;
    std::string salt;
    Balanta balanta;
    bool categorie;
    std::string categoryType;
    bool isValidated;
    std::string validationFileName;
    std::time_t validationExpiry;

    std::time_t addOneYear() const {
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

public:
    User() : categorie(false), isValidated(false), validationExpiry(0) {}

    User(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta, const bool& _categorie)
            : username(_username), parola(_parola), salt(_salt), balanta(_balanta), categorie(_categorie), isValidated(false), validationExpiry(0)
    {}

    User& operator=(const User& other) {
        username = other.username;
        parola = other.parola;
        salt = other.salt;
        balanta = other.balanta;
        categorie = other.categorie;
        categoryType = other.categoryType;
        isValidated = other.isValidated;
        validationFileName = other.validationFileName;
        validationExpiry = other.validationExpiry;
        return *this;
    }

    User(const User& other)
            : username(other.username), parola(other.parola), salt(other.salt), balanta(other.balanta), categorie(other.categorie),
              categoryType(other.categoryType), isValidated(other.isValidated), validationFileName(other.validationFileName), validationExpiry(other.validationExpiry)
    {}

    ~User() {}

    friend std::ostream& operator<<(std::ostream& os, const User& other) {
        os << "Username: " << other.username << ", Parola: " << other.parola << "\n" << other.balanta;
        if (other.isValidated) {
            char buffer[80];
            struct tm * timeinfo = localtime(&other.validationExpiry);
            strftime(buffer, 80, "%Y-%m-%d", timeinfo);
            os << ", Categorie: " << other.categoryType << ", Validat pana: " << buffer << "\n";
        }
        return os;
    }

    bool checkLogin(const std::string& _username, const std::string& _parola) const {
        std::string parolaHashed = PasswordManager::hash_password(_parola, salt);
        return (username == _username && parola == parolaHashed);
    }

    void setCategorie(bool categorieNoua) {
        categorie = categorieNoua;
    }

    void selectCategory() {
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

    void validateCategory() {
        // Here you can add code to actually validate the picture if needed.
        isValidated = true;
        validationExpiry = addOneYear();
        std::cout << "Licenta " << categoryType << " a fost validata si este valabila un an din acest moment.\n";
    }

    int reducere(const Film& film) const {
        if (categorie && film.getPret() > 20) {
            std::cout << "Biletul a fost redus la 15 lei deoarece esti " << categoryType << ".\n";
            return 15;
        }
        return film.getPret();
    }

    int getBalanta() const {
        return balanta.getSuma();
    }

    void adaugaInBalanta(int sumaAdaugata) {
        if (sumaAdaugata < 10 || sumaAdaugata > 500) {
            throw InvalidBalanceOperationException("Suma adaugata trebuie sa fie intre 10 si 500.");
        } else {
            balanta.adaugaSuma(sumaAdaugata);
        }
    }

    bool areBani(int pretBilet) const {
        return balanta.getSuma() >= pretBilet;
    }

    void scadeDinBalanta(int sumaScaduta) {
        try {
            balanta.adaugaSuma(-sumaScaduta);
            std::cout << "Noua balanta: " << balanta.getSuma() << "\n";
        } catch (const std::exception &e) {
            std::cerr << "Eroare la scaderea din balanta: " << e.what() << '\n';
        }
    }
};

#endif // OOP_USER_H
