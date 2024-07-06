#ifndef OOP_APLICATIE_H
#define OOP_APLICATIE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "passwordmanager.h"
#include "film.h"
#include "user.h"
#include "balanta.h"
#include "exceptieCustom.h"

class FileOpenException : public CustomException {
public:
    FileOpenException(const std::string &filename)
            : CustomException("Nu s-a putut deschide fisierul: " + filename) {}
};

class Aplicatie {
private:
    std::vector<Film> filme;
    User user;
public:
    Aplicatie() = default;

    Aplicatie(const std::vector<Film> &_filme, const User &_user)
            : filme(_filme), user(_user) {}

    Aplicatie(const Aplicatie &other)
            : filme(other.filme), user(other.user) {}

    Aplicatie &operator=(const Aplicatie &other) {
        if (this != &other) {
            filme = other.filme;
            user = other.user;
        }
        return *this;
    }

    ~Aplicatie() {}

    void signUp() {
        std::cout << "Bun venit la Movie Booking System! Te rog sa iti creezi un cont!\n";
        std::cout << "Username:";
        std::string username, parola;
        std::cin >> username;
        std::cout << "Parola:";
        std::cin >> parola;
        std::string salt = PasswordManager::make_salt();
        std::string parolaHashed = PasswordManager::hash_password(parola, salt);
        user = User(username, parolaHashed, salt, Balanta(0), false);
        std::cout << "\n";
    }

    bool logIn() {
        std::cout << "Te rog sa te conectezi!\n";
        std::cout << "Username:";
        std::string username, parola;
        std::cin >> username;
        std::cout << "Parola:";
        std::cin >> parola;
        if (!user.checkLogin(username, parola)) {
            std::cout << "Date de autentificare invalide.\n";
            return false;
        } else {
            return true;
        }
    }

    void initializareFilme() {
        std::ifstream file("filme.csv");

        if (!file.is_open()) {
            throw FileOpenException("filme.csv");
        }

        std::string line;
        while (std::getline(file, line)) {
            try {
                std::stringstream ss(line);
                std::string numeFilm;
                std::getline(ss, numeFilm, ',');

                std::string durataStr;
                std::getline(ss, durataStr, ',');
                int durata = std::stoi(durataStr);

                std::string pretStr;
                std::getline(ss, pretStr, ',');
                int pret = std::stoi(pretStr);

                std::vector<Actor> cast;
                std::string actorsStr;
                std::getline(ss, actorsStr, ',');
                std::stringstream ssActors(actorsStr);
                std::string actorStr;
                while (std::getline(ssActors, actorStr, ';')) {
                    std::stringstream ssActor(actorStr);
                    std::string nume;
                    std::getline(ssActor, nume, '-');
                    std::string varstaStr;
                    std::getline(ssActor, varstaStr);
                    int varsta = std::stoi(varstaStr);
                    cast.push_back(Actor(nume, varsta));
                }

                std::vector<std::string> schedule;
                std::string scheduleStr;
                std::getline(ss, scheduleStr);
                std::stringstream ssSchedule(scheduleStr);
                std::string date;
                while (std::getline(ssSchedule, date, ';')) {
                    schedule.push_back(date);
                }

                filme.push_back(Film(numeFilm, durata, pret, cast, schedule));
            } catch (const std::invalid_argument &e) {
                std::cout << "Eroare la procesarea liniei: " << line << "\n";
                std::cout << e.what() << '\n';
            }
        }

        file.close();
    }

    void cumparaBiletFilm() {
        for (size_t i = 0; i < filme.size(); ++i) {
            std::cout << i + 1 << ". ";
            filme[i].printFilmDetails();
        }

        size_t nr = filme.size();

        std::cout << "Alege un film pentru care vrei sa cumperi bilet:\n";

        size_t numar_selectat;
        std::cin >> numar_selectat;

        if (numar_selectat > nr) {
            std::cout << "Ai ales un numar prea mare care nu corespunde niciunui film!\n";
        } else {
            Film& filmSelectat = filme[numar_selectat - 1];

            std::cout << "Programari disponibile pentru " << filmSelectat.getNume() << ":\n";
            const auto& schedule = filmSelectat.getSchedule();
            for (size_t i = 0; i < schedule.size(); ++i) {
                std::cout << i + 1 << ". " << schedule[i] << "\n";
            }

            std::cout << "Alege o data si ora pentru care vrei sa cumperi bilet:\n";

            size_t data_selectata;
            std::cin >> data_selectata;

            if (data_selectata > schedule.size()) {
                std::cout << "Ai ales un numar prea mare care nu corespunde niciunei programari!\n";
            } else {
                int pretFinal = user.reducere(filmSelectat);
                if (user.areBani(pretFinal)) {
                    filmSelectat.printSeating();

                    std::cout << "Alege un rand (0-4):\n";
                    int row;
                    std::cin >> row;

                    std::cout << "Alege un loc (0-9):\n";
                    int col;
                    std::cin >> col;

                    if (row < 0 || row >= 5 || col < 0 || col >= 10) {
                        std::cout << "Rand sau loc invalid!\n";
                    } else if (!filmSelectat.isSeatFree(row, col)) {
                        std::cout << "Locul este deja ocupat!\n";
                    } else {
                        filmSelectat.occupySeat(row, col);
                        std::cout << "Felicitari! Ai cumparat bilet pentru data " << schedule[data_selectata - 1] << " la randul " << row << " locul " << col << "!\n";
                        user.scadeDinBalanta(pretFinal);
                    }
                } else {
                    std::cout << "Nu ai suficienti bani pentru a cumpara biletul.\n";
                    std::cout << "Balanta curenta: " << user.getBalanta() << "\n";
                }
            }
        }
    }

    void selectareCategorie() {
        user.selectCategory();
    }

    void gestionareBalanta() {
        std::cout << "1. Adauga bani in balanta\n";
        std::cout << "2. Vezi istoricul tranzactiilor\n";
        int optiune;
        std::cin >> optiune;

        if (optiune == 1) {
            adaugaBaniInBalanta();
        } else if (optiune == 2) {
            user.getBalantaObject().afisareIstoricTranzactii();
        } else {
            std::cout << "Optiune invalida.\n";
        }
    }

private:
    void adaugaBaniInBalanta() {
        std::cout << "Balanta curenta: " << user.getBalanta() << "\n";
        std::cout << "Introdu suma pe care vrei sa o adaugi in balanta:";
        int sumaAdaugata;
        std::cin >> sumaAdaugata;
        std::cout << "\n";

        std::cout << "Selecteaza metoda de plata: [1/2]\n";
        std::cout << "1. Card\n";
        std::cout << "2. PayPal\n";
        int metoda;
        std::cin >> metoda;
        std::cout << "\n";

        std::unique_ptr<PaymentMethod> paymentMethod;
        if (metoda == 1) {
            paymentMethod = std::make_unique<Card>();
        } else if (metoda == 2) {
            paymentMethod = std::make_unique<PayPal>();
        } else {
            std::cout << "Metoda de plata invalida.\n";
            return;
        }

        if (sumaAdaugata < 10 || sumaAdaugata > 500) {
            std::cout << "Suma adaugata trebuie sa fie intre 10 si 500.\n";
        } else {
            std::cout << "Plata in curs...\n";
            try {
                paymentMethod->pay(sumaAdaugata);
                user.adaugaInBalanta(sumaAdaugata);
                std::cout << "Noua balanta: " << user.getBalanta() << "\n";
            } catch (const CustomException &e) {
                std::cout << "Eroare la procesarea platii: " << e.what() << '\n';
            }
        }
    }
};

#endif // OOP_APLICATIE_H
