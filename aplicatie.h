#ifndef OOP_APLICATIE_H
#define OOP_APLICATIE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "passwordmanager.h"
#include "film.h"
#include "user.h"
#include "balanta.h"
#include "exceptieCustom.h"
#include "admin.h"

class FileOpenException : public CustomException {
public:
    FileOpenException(const std::string &filename)
            : CustomException("Nu s-a putut deschide fisierul: " + filename) {}
};


class InvalidDateException : public CustomException {
public:
    InvalidDateException(const std::string &date)
            : CustomException("Data invalida: " + date) {}
};

class InvalidTimeException : public CustomException {
public:
    InvalidTimeException(const std::string &time)
            : CustomException("Ora invalida: " + time) {}
};

class InvalidChoiceException : public CustomException {
public:
    InvalidChoiceException(const std::string &choice)
            : CustomException("Optiune invalida: " + choice) {}
};

class Aplicatie {
private:
    std::vector<Film> filme;
    std::vector<User*> utilizatori;
    User* userCurent;

    bool isValidDate(const std::string& date) {
        std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");
        return std::regex_match(date, datePattern);
    }

    bool isValidTime(const std::string& time) {
        std::regex timePattern(R"(\d{2}:\d{2})");
        return std::regex_match(time, timePattern);
    }

    void loadUsers() {
        std::ifstream file("users.csv");

        if (!file.is_open()) {
            throw FileOpenException("users.csv");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string username, parola, salt, balantaStr, categorieStr, role;
            bool categorie;
            int balanta;

            std::getline(ss, username, ',');
            std::getline(ss, parola, ',');
            std::getline(ss, salt, ',');
            std::getline(ss, balantaStr, ',');
            balanta = std::stoi(balantaStr);
            std::getline(ss, categorieStr, ',');
            categorie = (categorieStr == "1");
            std::getline(ss, role, ',');

            if (role == "admin") {
                utilizatori.push_back(new Admin(username, parola, salt, Balanta(balanta)));
            } else {
                utilizatori.push_back(new User(username, parola, salt, Balanta(balanta), categorie));
            }
        }

        file.close();
    }

    void saveUsers() {
        std::ofstream file("users.csv");

        if (!file.is_open()) {
            throw FileOpenException("users.csv");
        }

        for (const auto& user : utilizatori) {
            file << user->getUsername() << "," << user->getParola() << "," << user->getSalt() << ","
                 << user->getBalanta() << "," << user->isCategorie() << "," << user->getRole() << "\n";
        }

        file.close();
    }

public:
    Aplicatie() : userCurent(nullptr) {
        loadUsers();
    }

    Aplicatie(const std::vector<Film> &_filme, const std::vector<User*> &_utilizatori)
            : filme(_filme), utilizatori(_utilizatori), userCurent(nullptr) {
        loadUsers();
    }

    ~Aplicatie() {
        saveUsers();
        for (auto user : utilizatori) {
            delete user;
        }
    }

    void signUp() {
        std::cout << "Creeaza un cont nou!\n";
        std::cout << "Username:";
        std::string username, parola;
        std::cin >> username;
        std::cout << "Parola:";
        std::cin >> parola;
        std::string salt = PasswordManager::make_salt();
        std::string parolaHashed = PasswordManager::hash_password(parola, salt);

        std::cout << "Selecteaza rol: [1] User, [2] Admin\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            utilizatori.push_back(new User(username, parolaHashed, salt, Balanta(0), false));
        } else if (choice == 2) {
            utilizatori.push_back(new Admin(username, parolaHashed, salt, Balanta(0)));
        } else {
            throw InvalidChoiceException(std::to_string(choice));
        }

        saveUsers();
        std::cout << "Cont creat cu succes!\n";
    }

    bool logIn() {
        std::cout << "Te rog sa te conectezi!\n";
        std::cout << "Username:";
        std::string username, parola;
        std::cin >> username;
        std::cout << "Parola:";
        std::cin >> parola;

        for (auto user : utilizatori) {
            if (user->checkLogin(username, parola)) {
                userCurent = user;
                std::cout << "Conectare reușită!\n";
                return true;
            }
        }

        std::cout << "Date de autentificare invalide.\n";
        return false;
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

    void meniuUtilizator() {
        if (!userCurent) {
            std::cout << "Niciun utilizator conectat.\n";
            return;
        }

        int optiune;
        do {
            std::cout << "Alegi ce vrei sa faci:\n";
            std::cout << "1. Alege un film\n";
            std::cout << "2. Actualizeaza categoria\n";
            std::cout << "3. Gestioneaza balanta\n";
            std::cout << "4. Creeaza cont nou\n";
            if (dynamic_cast<Admin*>(userCurent)) {
                std::cout << "5. Meniu admin\n";
                std::cout << "6. Deconecteaza-te\n";
            } else {
                std::cout << "5. Deconecteaza-te\n";
            }
            std::cin >> optiune;

            try {
                switch (optiune) {
                    case 1:
                        cumparaBiletFilm();
                        break;
                    case 2:
                        selectareCategorie();
                        break;
                    case 3:
                        gestionareBalanta();
                        break;
                    case 4:
                        signUp();
                        break;
                    case 5:
                        if (dynamic_cast<Admin*>(userCurent)) {
                            adminMenu();
                        } else {
                            userCurent = nullptr;
                            std::cout << "Te-ai deconectat.\n";
                            return;
                        }
                        break;
                    case 6:
                        userCurent = nullptr;
                        std::cout << "Te-ai deconectat.\n";
                        return;
                    default:
                        throw InvalidChoiceException(std::to_string(optiune));
                }
            } catch (const CustomException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
        } while (optiune != 5 || (dynamic_cast<Admin*>(userCurent) && optiune != 6));
    }

    void adminMenu() {
        Admin* admin = dynamic_cast<Admin*>(userCurent);
        if (!admin) {
            std::cout << "Nu ai acces la meniul de administrare.\n";
            return;
        }

        int optiune;
        do {
            std::cout << "Meniu admin:\n";
            std::cout << "1. Adauga film\n";
            std::cout << "2. Modifica pret film\n";
            std::cout << "3. Modifica program film\n";
            std::cout << "4. Inapoi la meniul principal\n";
            std::cin >> optiune;

            try {
                switch (optiune) {
                    case 1:
                        adaugaFilm(admin);
                        break;
                    case 2:
                        modificaPretFilm(admin);
                        break;
                    case 3:
                        modificaProgramFilm(admin);
                        break;
                    case 4:
                        return;
                    default:
                        throw InvalidChoiceException(std::to_string(optiune));
                }
            } catch (const CustomException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
        } while (optiune != 4);
    }

    void adaugaFilm(Admin* admin) {
        std::string nume;
        int durata, pret;
        std::vector<Actor> cast;
        std::vector<std::string> schedule;

        std::cout << "Introdu numele filmului: ";
        std::cin.ignore();
        std::getline(std::cin, nume);

        std::cout << "Introdu durata filmului (minute): ";
        std::cin >> durata;

        std::cout << "Introdu pretul filmului (RON): ";
        std::cin >> pret;

        int nrActori;
        std::cout << "Introdu numarul de actori: ";
        std::cin >> nrActori;

        for (int i = 0; i < nrActori; ++i) {
            std::string numeActor;
            int varsta;
            std::cout << "Introdu numele actorului: ";
            std::cin.ignore();
            std::getline(std::cin, numeActor);

            std::cout << "Introdu varsta actorului: ";
            std::cin >> varsta;

            cast.push_back(Actor(numeActor, varsta));
        }

        int nrProgramari;
        std::cout << "Introdu numarul de programari: ";
        std::cin >> nrProgramari;

        for (int i = 0; i < nrProgramari; ++i) {
            std::string program;
            std::cout << "Introdu programarea (e.g., 2024-07-08 19:00): ";
            std::cin.ignore();
            std::getline(std::cin, program);
            if (!isValidDate(program.substr(0, 10))) {
                throw InvalidDateException(program.substr(0, 10));
            }
            if (!isValidTime(program.substr(11))) {
                throw InvalidTimeException(program.substr(11));
            }
            schedule.push_back(program);
        }

        admin->adaugaFilm(filme, Film(nume, durata, pret, cast, schedule));
    }

    void modificaPretFilm(Admin* admin) {
        int index, pretNou;
        std::cout << "Selecteaza indexul filmului: ";
        std::cin >> index;

        if (index < 1 || index > filme.size()) {
            throw InvalidChoiceException(std::to_string(index));
        }

        std::cout << "Introdu pretul nou: ";
        std::cin >> pretNou;

        admin->modificaPretFilm(filme[index - 1], pretNou);
    }

    void modificaProgramFilm(Admin* admin) {
        int index, nrProgramari;
        std::vector<std::string> programNou;

        std::cout << "Selecteaza indexul filmului: ";
        std::cin >> index;

        if (index < 1 || index > filme.size()) {
            throw InvalidChoiceException(std::to_string(index));
        }

        std::cout << "Introdu numarul de programari noi: ";
        std::cin >> nrProgramari;

        for (int i = 0; i < nrProgramari; ++i) {
            std::string program;
            std::cout << "Introdu programarea (e.g., 2024-07-08 19:00): ";
            std::cin.ignore();
            std::getline(std::cin, program);
            if (!isValidDate(program.substr(0, 10))) {
                throw InvalidDateException(program.substr(0, 10));
            }
            if (!isValidTime(program.substr(11))) {
                throw InvalidTimeException(program.substr(11));
            }
            programNou.push_back(program);
        }

        admin->modificaProgramFilm(filme[index - 1], programNou);
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
            throw InvalidChoiceException(std::to_string(numar_selectat));
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
                throw InvalidChoiceException(std::to_string(data_selectata));
            } else {
                int pretFinal = userCurent->reducere(filmSelectat);
                if (userCurent->areBani(pretFinal)) {
                    filmSelectat.printSeating();

                    std::cout << "Alege un rand (0-4):\n";
                    int row;
                    std::cin >> row;

                    std::cout << "Alege un loc (0-9):\n";
                    int col;
                    std::cin >> col;

                    if (row < 0 || row >= 5 || col < 0 || col >= 10) {
                        throw InvalidChoiceException("Rand sau loc invalid");
                    } else if (!filmSelectat.isSeatFree(row, col)) {
                        std::cout << "Locul este deja ocupat!\n";
                    } else {
                        filmSelectat.occupySeat(row, col);
                        std::cout << "Felicitari! Ai cumparat bilet pentru data " << schedule[data_selectata - 1] << " la randul " << row << " locul " << col << "!\n";
                        userCurent->scadeDinBalanta(pretFinal);
                    }
                } else {
                    std::cout << "Nu ai suficienti bani pentru a cumpara biletul.\n";
                    std::cout << "Balanta curenta: " << userCurent->getBalanta() << "\n";
                }
            }
        }
    }

    void selectareCategorie() {
        userCurent->selectCategory();
    }

    void gestionareBalanta() {
        std::cout << "1. Adauga bani in balanta\n";
        std::cout << "2. Vezi istoricul tranzactiilor\n";
        int optiune;
        std::cin >> optiune;

        try {
            switch (optiune) {
                case 1:
                    adaugaBaniInBalanta();
                    break;
                case 2:
                    userCurent->getBalantaObject().afisareIstoricTranzactii();
                    break;
                default:
                    throw InvalidChoiceException(std::to_string(optiune));
            }
        } catch (const CustomException& e) {
            std::cout << "Eroare: " << e.what() << "\n";
        }
    }

private:
    void adaugaBaniInBalanta() {
        std::cout << "Balanta curenta: " << userCurent->getBalanta() << "\n";
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
            throw InvalidChoiceException(std::to_string(metoda));
        }

        if (sumaAdaugata < 10 || sumaAdaugata > 500) {
            throw CustomException("Suma adaugata trebuie sa fie intre 10 si 500.");
        } else {
            std::cout << "Plata in curs...\n";
            try {
                paymentMethod->pay(sumaAdaugata);
                userCurent->adaugaInBalanta(sumaAdaugata);
                std::cout << "Noua balanta: " << userCurent->getBalanta() << "\n";
            } catch (const CustomException &e) {
                std::cout << "Eroare la procesarea platii: " << e.what() << '\n';
            }
        }
    }
};

#endif // OOP_APLICATIE_H
