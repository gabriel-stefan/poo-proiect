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

class Aplicatie : public Singleton<Aplicatie> {
private:
    std::vector<Film> filme;
    std::vector<User*> utilizatori;
    User* userCurent;

    friend class Singleton<Aplicatie>;
    Aplicatie(); // Constructor privat

    bool isValidDate(const std::string& date);
    bool isValidTime(const std::string& time);
    void loadUsers();
    void saveUsers();
    void initializareFilme();

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

private:
    void adaugaBaniInBalanta();
};

#endif // OOP_APLICATIE_H
