#ifndef OOP_USER_H
#define OOP_USER_H

#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "film.h"
#include "passwordmanager.h"
#include "balanta.h"
#include "exceptieCustom.h"

class User {
protected:
    std::string username;
    std::string parola;
    std::string salt;
    Balanta balanta;
    bool categorie;
    std::string categoryType;
    bool isValidated;
    std::string validationFileName;
    std::time_t validationExpiry;
    std::string role;

    std::time_t addOneYear() const;

public:
    User();
    User(const std::string& _username, const std::string& _parola, const std::string& _salt, const Balanta& _balanta, const bool& _categorie, const std::string& _role = "user");

    User& operator=(const User& other);
    User(const User& other);
    virtual ~User();

    friend std::ostream& operator<<(std::ostream& os, const User& other);

    bool checkLogin(const std::string& _username, const std::string& _parola) const;
    void setCategorie(bool categorieNoua);
    void selectCategory();
    void validateCategory();
    int reducere(const Film& film) const;

    int getBalanta() const;
    Balanta& getBalantaObject();
    void adaugaInBalanta(int sumaAdaugata);
    bool areBani(int pretBilet) const;
    void scadeDinBalanta(int sumaScazuta);
    std::string getRole() const;

    const std::string& getUsername() const;
    const std::string& getParola() const;
    const std::string& getSalt() const;
    bool isCategorie() const;

    void writeToFile(std::ofstream& file) const;
};

#endif // OOP_USER_H
