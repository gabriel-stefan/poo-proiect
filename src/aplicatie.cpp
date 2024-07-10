#include "../Headers/aplicatie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <csv.hpp>
#include "../Headers/userbuilder.h"
#include "../Headers/filmfactory.h"
#include "../Headers/admin.h"
#include "../Headers/card.h"
#include "../Headers/paypal.h"
#include "../Headers/paymentMethod.h"


FileOpenException::FileOpenException(const std::string &filename)
        : CustomException("Nu s-a putut deschide fisierul: " + filename) {}

InvalidDateException::InvalidDateException(const std::string &date)
        : CustomException("Data invalida: " + date) {}

InvalidTimeException::InvalidTimeException(const std::string &time)
        : CustomException("Ora invalida: " + time) {}

InvalidChoiceException::InvalidChoiceException(const std::string &choice)
        : CustomException("Optiune invalida: " + choice) {}

UserAlreadyExistsException::UserAlreadyExistsException(const std::string &username)
        : CustomException("Username-ul " + username + " exista deja.") {}

bool Aplicatie::isValidDate(const std::string& date) {
    std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return std::regex_match(date, datePattern);
}

bool Aplicatie::isValidTime(const std::string& time) {
    std::regex timePattern(R"(\d{2}:\d{2})");
    return std::regex_match(time, timePattern);
}

void Aplicatie::loadUsers() {
    csv::CSVReader in("users.csv");

    for (csv::CSVRow& row: in) {
        std::string username = row["username"].get<>();
        std::string parola = row["parola"].get<>();
        std::string salt = row["salt"].get<>();
        int balanta = row["balanta"].get<int>();
        bool categorie = row["categorie"].get<bool>();
        std::string role = row["role"].get<>();

        if (role == "admin") {
            utilizatori.push_back(new Admin(username, parola, salt, Balanta(balanta)));
        } else {
            utilizatori.push_back(new User(username, parola, salt, Balanta(balanta), categorie));
        }
    }
}


void Aplicatie::saveUsers() {
    std::ofstream file("users.csv");
    if (!file.is_open()) {
        throw FileOpenException("users.csv");
    }

    file << "username,parola,salt,balanta,categorie,role\n";
    for (const auto& user : utilizatori) {
        user->writeToFile(file);
    }

    file.close();
}

bool Aplicatie::userExists(const std::string& username) {
    for (const auto& user : utilizatori) {
        if (user->getUsername() == username) {
            return true;
        }
    }
    return false;
}

void Aplicatie::deleteUser(const std::string& username) {
    auto it = std::remove_if(utilizatori.begin(), utilizatori.end(), [&username](User* user) {
        return user->getUsername() == username;
    });

    if (it != utilizatori.end()) {
        delete *it;
        utilizatori.erase(it);
        saveUsers();
        std::cout << "User-ul " << username << " a fost sters cu succes.\n";
    } else {
        throw CustomException("User-ul " + username + " nu exista.");
    }
}

Aplicatie::Aplicatie() : userCurent(nullptr) {
    loadUsers();
    initializareFilme();
}

Aplicatie::~Aplicatie() {
    saveUsers();
    for (auto user : utilizatori) {
        delete user;
    }
}

void Aplicatie::initializareFilme() {
    csv::CSVReader in("filme.csv");

    for (csv::CSVRow& row: in) {
        std::string numeFilm, castStr, scheduleStr;
        int durata, pret;

        try {
            numeFilm = row["numeFilm"].get<>();
            durata = row["durata"].get<int>();
            pret = row["pret"].get<int>();
            castStr = row["cast"].get<>();
            scheduleStr = row["schedule"].get<>();

            std::vector<Actor> cast;
            std::stringstream ssActors(castStr);
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
            std::stringstream ssSchedule(scheduleStr);
            std::string date;
            while (std::getline(ssSchedule, date, ';')) {
                schedule.push_back(date);
            }

            filme.push_back(FilmFactory::createFilm(numeFilm, durata, pret, cast, schedule));
        } catch (const std::invalid_argument &e) {
            std::cout << "Eroare la procesarea liniei: " << numeFilm << "\n";
            std::cout << e.what() << '\n';
        }
    }
}



void Aplicatie::signUp() {
    std::cout << "Creeaza un cont nou!\n";
    std::cout << "Username:";
    std::string username, parola;
    std::cin >> username;

    if (userExists(username)) {
        throw UserAlreadyExistsException(username);
    }

    std::cout << "Parola:";
    std::cin >> parola;
    std::string salt = PasswordManager::make_salt();
    std::string parolaHashed = PasswordManager::hash_password(parola, salt);

    std::cout << "Selecteaza rol: [1] User, [2] Admin\n";
    int choice;
    std::cin >> choice;

    UserBuilder builder;
    builder.setUsername(username)
            .setParola(parolaHashed)
            .setSalt(salt)
            .setBalanta(Balanta(0));

    if (choice == 1) {
        builder.setCategorie(false).setRole("user");
    } else if (choice == 2) {
        builder.setRole("admin");
    } else {
        throw InvalidChoiceException(std::to_string(choice));
    }

    utilizatori.push_back(new User(builder.build()));
    saveUsers();
    std::cout << "Cont creat cu succes!\n";
}

bool Aplicatie::logIn() {
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

void Aplicatie::meniuUtilizator() {
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
        std::cout << "5. Sterge cont\n";
        if (dynamic_cast<Admin*>(userCurent)) {
            std::cout << "6. Meniu admin\n";
            std::cout << "7. Deconecteaza-te\n";
        } else {
            std::cout << "6. Deconecteaza-te\n";
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
                {
                    std::cout << "Introdu username-ul contului pe care doresti sa il stergi: ";
                    std::string username;
                    std::cin >> username;
                    deleteUser(username);
                }
                    break;
                case 6:
                    if (dynamic_cast<Admin*>(userCurent)) {
                        adminMenu();
                    } else {
                        userCurent = nullptr;
                        std::cout << "Te-ai deconectat.\n";
                        return;
                    }
                    break;
                case 7:
                    if (dynamic_cast<Admin*>(userCurent)) {
                        userCurent = nullptr;
                        std::cout << "Te-ai deconectat.\n";
                        return;
                    }
                    break;
                default:
                    throw InvalidChoiceException(std::to_string(optiune));
            }
        } catch (const CustomException& e) {
            std::cout << "Eroare: " << e.what() << "\n";
        }
    } while ((dynamic_cast<Admin*>(userCurent) && optiune != 7) || optiune != 6);
}


void Aplicatie::adminMenu() {
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

void Aplicatie::adaugaFilm(Admin* admin) {
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

    admin->adaugaFilm(filme, FilmFactory::createFilm(nume, durata, pret, cast, schedule));
}

void Aplicatie::modificaPretFilm(Admin* admin) {
    int index, pretNou;
    std::cout << "Selecteaza indexul filmului: ";
    std::cin >> index;

    if (index < 1 || static_cast<size_t>(index) > filme.size()) {
        throw InvalidChoiceException(std::to_string(index));
    }

    std::cout << "Introdu pretul nou: ";
    std::cin >> pretNou;

    admin->modificaPretFilm(filme[index - 1], pretNou);
}

void Aplicatie::modificaProgramFilm(Admin* admin) {
    int index, nrProgramari;
    std::vector<std::string> programNou;

    std::cout << "Selecteaza indexul filmului: ";
    std::cin >> index;

    if (index < 1 || static_cast<size_t>(index) > filme.size()) {
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

void Aplicatie::cumparaBiletFilm() {
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

void Aplicatie::selectareCategorie() {
    userCurent->selectCategory();
}

void Aplicatie::gestionareBalanta() {
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

void Aplicatie::adaugaBaniInBalanta() {
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
