#include <iostream>
#include <vector>
#include <chrono>
//#include <functional>
#include <fstream>
//#include <digestpp.hpp> <---- nu pot sa rezolv aici
//#include <thread>
//#include <SFML/Graphics.hpp>
//#include <Helper.h>
//#include "env_fixes.h"

//class PasswordManager {
//public:
//    static std::string make_salt() {
//        static uint64_t nr = 1u;
//        std::string salt;
//        auto bytes = static_cast<char*>(static_cast<void*>(&nr));
//        for(unsigned i = 0; i < 16; i++) {
//            salt += bytes[i%8];
//        }
//        ++nr;
//        return salt;
//    }
//
//    static std::string hash_password(const std::string& plain, const std::string& salt) {
//        return digestpp::blake2b(512).set_salt(salt).absorb(plain).hexdigest();
//    }
//};

class Actor{
private:
    std::string nume;
    int varsta;
public:
    Actor() = default;

    Actor(const std::string& _nume, const int _varsta)
            :nume(_nume), varsta(_varsta)
    {}

    Actor& operator=(const Actor& other){
        nume = other.nume;
        varsta = other.varsta;
        return *this;
    }

    Actor(const Actor& other)
            : nume(other.nume), varsta(other.varsta)
    {}

    ~Actor(){}

    friend std::ostream& operator<<(std::ostream& os, const Actor& other) {
        os << other.nume << ", " << other.varsta << " ani ";
        return os;
    }
};

class Film{
private:
    std::string nume;
    int durata;
    int pret;
    std::vector<Actor> cast;
public:
    Film() = default;

    Film(const std::string& _nume, const int _durata, const int& _pret, const std::vector<Actor>& _cast)
            :nume(_nume), durata(_durata), pret(_pret), cast(_cast)
    {}

    Film& operator=(const Film& other){
        nume = other.nume;
        durata = other.durata;
        cast = other.cast;
        pret = other.pret;
        return *this;
    }

    Film(const Film& other)
            : nume(other.nume), durata(other.durata), pret(other.pret), cast(other.cast)
    {}

    ~Film(){}

    friend std::ostream& operator<<(std::ostream& os, const Film& other) {
        os << "Nume film: " << other.nume << ", Durata: " << other.durata << ", Pret: " << other.pret << "\n";
        os << "Actori: ";
        for (auto it = other.cast.begin(); it != other.cast.end(); ++it) {
            os << *it;
            if (it != other.cast.end() - 1) {
                os << ", ";
            }
        }
        return os;
    }

    int getPret() const {
        return pret;
    }

    void setPret(int newPret) {
        pret = newPret;
    }
};

class Balanta{    //o sa mai fie aici adaugate metode de plata
private:
    int suma;
public:
    Balanta() = default;

    Balanta(const int _suma)
            :suma(_suma)
    {}

    Balanta& operator=(const Balanta& other){
        suma = other.suma;
        return *this;
    }

    Balanta(const Balanta& other)
            : suma(other.suma)
    {}

    int getSuma() const {
        return suma;
    }

    ~Balanta(){}

    void adaugaSuma(int sumaAdaugata) {
        suma += sumaAdaugata;
    }

    friend std::ostream& operator<<(std::ostream& os, const Balanta& other) {
        os << "Balanta: " << other.suma << "\n";
        return os;
    }

};

class User{
private:
    std::string username;
    std::string parola;
    Balanta balanta;
    bool categorie;
public:
    User() = default;

    User(const std::string& _username, const std::string& _parola, const Balanta& _balanta, const bool& _categorie)
        :username(_username), parola(_parola), balanta(_balanta), categorie(_categorie)
    {}

    User& operator=(const User& other){
        username = other.username;
        parola = other.parola;
        balanta = other.balanta;
        categorie = other.categorie;
        return *this;
    }

    User(const User& other)
            : username(other.username), parola(other.parola), balanta(other.balanta), categorie(other.categorie)
    {}

    ~User(){}

    friend std::ostream& operator<<(std::ostream& os, const User& other) {
        os << "Username: " << other.username << ", Parola: " << other.parola << "\n" << other.balanta;
        return os;
    }

    void setUsername(const std::string& usernameNou) {
        username = usernameNou;
    }

    void setPassword(const std::string& parolaNoua) {
        std::hash<std::string> hasher;
        parola = std::to_string(hasher(parolaNoua));
    }

    bool checkLogin(const std::string& _username, const std::string& _parola) const {
        std::hash<std::string> hasher;
        std::string hashed_parola = std::to_string(hasher(_parola));
        return (username == _username && parola == hashed_parola);
    }

    void setCategorie(bool categorieNoua) {
        categorie = categorieNoua;
    }

    void reducere(Film& film) {
        if (categorie == true && film.getPret() > 20) {
            film.setPret(15);
            std::cout << "Biletul a fost redus la 15 lei deoarece esti student." << std::endl;
        }
    }

    int getBalanta() const {
        return balanta.getSuma();
    }

    void adaugaInBalanta(int sumaAdaugata) {
        if (sumaAdaugata < 10 || sumaAdaugata > 500) {
            std::cout << "Suma adaugata trebuie sa fie intre 10 si 500.\n";
        } else {
            balanta.adaugaSuma(sumaAdaugata);
        }
    }

    bool areBani(int pretBilet) const {
        return balanta.getSuma() >= pretBilet;
    }

    void scadeDinBalanta(int sumaScaduta) {
        balanta.adaugaSuma(-sumaScaduta);
        std::cout << "Noua balanta: " << balanta.getSuma() << "\n";
    }

};

class Aplicatie{
private:
    std::vector<Film> filme;
    User user;
public:
    Aplicatie() = default;

    Aplicatie(const std::vector<Film>& _filme, const User& _user)
            : filme(_filme), user(_user)
    {}

    Aplicatie(const Aplicatie& other)
            : filme(other.filme), user(other.user)
    {}

    Aplicatie& operator=(const Aplicatie& other){
        if (this != &other) {
            filme = other.filme;
            user = other.user;
        }
        return *this;
    }

    ~Aplicatie(){}

    void signUp() {
        std::cout << "Bun venit la Movie Booking System! Te rog sa iti creezi un cont!\n";
        std::cout << "Username:";
        std::string username, parola;
        std::cin >> username;
        std::cout << "Parola:";
        std::cin >> parola;
        std::hash<std::string> hasher;
        std::string hashed_parola = std::to_string(hasher(parola));
        user = User(username,hashed_parola, Balanta(0), false);
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
            return false;
        }
        else {
            return true;
        }
    }

    void initializareFilme() {
        std::ifstream file("filme.csv");

        if (!file.is_open()) {
            std::cerr << "Nu s-a putut deschide fisierul'filme.csv'" << '\n';
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string nume;
            std::getline(ss, nume, ',');

            std::string durataStr;
            std::getline(ss, durataStr, ',');
            int durata;
            try {
                durata = std::stoi(durataStr);
            } catch (std::invalid_argument&) {
                std::cerr << "Durata invalida: " << durataStr << '\n';
                continue;
            }

            std::string pretStr;
            std::getline(ss, pretStr, ',');
            int pret;
            try {
                pret = std::stoi(pretStr);
            } catch (std::invalid_argument&) {
                std::cerr << "Pret invalid: " << pretStr << '\n';
                continue;
            }

            std::vector<Actor> cast;
            std::string actorsStr;
            std::getline(ss, actorsStr);
            std::stringstream ssActors(actorsStr);
            std::string actorStr;
            while (std::getline(ssActors, actorStr, ';')) {
                std::stringstream ssActor(actorStr);
                std::string nume;
                std::getline(ssActor, nume, '-');
                std::string varstaStr;
                std::getline(ssActor, varstaStr);
                int varsta;
                try {
                    varsta = std::stoi(varstaStr);
                } catch (std::invalid_argument&) {
                    std::cerr << "Varsta invalida: " << varstaStr << '\n';
                    continue;
                }
                cast.push_back(Actor(nume, varsta));
            }

            filme.push_back(Film(nume, durata, pret, cast));
        }

        file.close();
    }

    void cumparaBiletFilm() {
        for (size_t i = 0; i < filme.size(); ++i) {
            std::cout << i + 1 << ". " << filme[i] << "\n\n";
        }

        size_t nr = filme.size();

        std::cout << "Alege un film pentru care vrei sa cumperi bilet:\n";

        size_t numar_selectat;
        std::cin >> numar_selectat;

        if (numar_selectat > nr) {
            std::cout << "Ai ales un numar prea mare care nu corespunde niciunui film!\n";
        } else {
            if (user.areBani(filme[numar_selectat - 1].getPret())) {
                user.reducere(filme[numar_selectat - 1]);
                std::cout << "Felicitari! Ai cumparat bilet!\n";
                user.scadeDinBalanta(filme[numar_selectat - 1].getPret());
            } else {
                std::cout << "Nu ai suficienti bani pentru a cumpara biletul.\n";
                std::cout << "Balanta curenta: " << user.getBalanta() << "\n";
            }
        }
    }

    void selectareCategorie() {
        std::cout << "Te incadrezi intr-o categorie speciala de varsta?(student/pensionar) [y/n]";
        std::string raspuns;
        std::cin >> raspuns;
        if (raspuns == "y") {
            user.setCategorie(true);
            std::cout << "Beneficiezi de reduceri la filmele care sunt mai scumpe de 20 RON!\n";
        } else if (raspuns == "n"){
            user.setCategorie(false);
            std::cout << "Nu beneficiezi de reducere.\n";
        }
        else{
            std::cout << "Valoare invalida!\n";
        }
    }

    void gestionareBalanta() {
        std::cout << "Balanta curenta: " << user.getBalanta() << "\n";
        std::cout << "Introdu suma pe care vrei sa o adaugi in balanta:";
        int sumaAdaugata;
        std::cin >> sumaAdaugata;
        user.adaugaInBalanta(sumaAdaugata);
        std::cout << "Noua balanta: " << user.getBalanta() << "\n";
    }
};

int main() {

    Aplicatie app;
    app.initializareFilme();

    app.signUp();
    bool valid = 0;
    while(!valid){
        valid = app.logIn();
        if (!valid) {
            std::cout << "Datele de contectare nu sunt corecte.\n";
            std::cout << "Incearca din nou.\n\n";
        }
        else {
            std::cout << "Te-ai conectat cu succes!\n\n";
            valid = 1;
        }
    }

    bool ruleaza = true;
    while (ruleaza) {
        std::cout << "Alegi ce vrei sa faci:\n1. Alege un film\n2. Actualizeaza categoria\n3. Gestioneaza balata\n"; //urmeaza sa fie adaugate mai multe lucruri (adauga o metoda de plata, schimba cinema-ul etc.)
        std::cout << "[Introdu un numar]:";
        std::string alegere;
        std::cin >> alegere;
        std::cout << '\n';

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valoare invalida, te rog incearca din nou.\n\n";
            continue;
        }

        if (alegere == "1") {
            app.cumparaBiletFilm();
        } else if (alegere == "2") {
            app.selectareCategorie();
        }
        else if (alegere == "3") {
            app.gestionareBalanta();
        }
        else {
            std::cout << "Valoare invalida!\n";
            continue;
        }
        std::cout << "\nDoresti sa mai faci ceva? [y/n]";
        std::cin >> alegere;
        std::cout << "\n";
        if(alegere == "y"){
            ruleaza = true;
        }
        else if (alegere == "n"){
            ruleaza = false;
        }
        else {
            std::cout << "Valoare invalida!\n";
            continue;
        }
    }

    return 0;
}

