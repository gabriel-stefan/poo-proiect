#ifndef OOP_APLICATIE_H
#define OOP_APLICATIE_H

#include <string>
#include <vector>
#include <regex>
#include "passwordmanager.h"
#include "film.h"
#include "user.h"
#include "balanta.h"
#include "exceptieCustom.h"
#include "admin.h"
#include "Singleton.h"
#include "csv.hpp"

class FileOpenException : public CustomException {
public:
    explicit FileOpenException(const std::string &filename);
};

class InvalidDateException : public CustomException {
public:
    explicit InvalidDateException(const std::string &date);
};

class InvalidTimeException : public CustomException {
public:
    explicit InvalidTimeException(const std::string &time);
};

class InvalidChoiceException : public CustomException {
public:
    explicit InvalidChoiceException(const std::string &choice);
};

class UserAlreadyExistsException : public CustomException {
public:
    explicit UserAlreadyExistsException(const std::string &username);
};

class Aplicatie : public Singleton<Aplicatie> {
private:
    std::vector<Film> filme;
    std::vector<User*> utilizatori;
    User* userCurent;

    friend class Singleton<Aplicatie>;
    Aplicatie();

    bool isValidDate(const std::string& date);
    bool isValidTime(const std::string& time);
    void loadUsers();
    void saveUsers();
    void initializareFilme();
    bool userExists(const std::string& username);

public:
    ~Aplicatie();

    void signUp();
    bool logIn();
    void meniuUtilizator();
    void adminMenu();
    void adaugaFilm(Admin* admin);
    void modificaPretFilm(Admin* admin);
    void modificaProgramFilm(Admin* admin);
    void cumparaBiletFilm();
    void selectareCategorie();
    void gestionareBalanta();
    void deleteUser(const std::string& username);

private:
    void adaugaBaniInBalanta();
};

#endif // OOP_APLICATIE_H
