#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
//#include <thread>
//#include <SFML/Graphics.hpp>
//#include <Helper.h>
//#include "env_fixes.h"

class Actor{
private:
    std::string nume;
    int varsta;
    std::vector<std::string> filmeJucate;
public:
    Actor() = default;

    Actor(const std::string& _nume, const int _varsta, const std::vector<std::string>& _filmeJucate)
            :nume(_nume), varsta(_varsta), filmeJucate(_filmeJucate)
    {}

    Actor& operator=(const Actor& other){
        nume = other.nume;
        varsta = other.varsta;
        filmeJucate = other.filmeJucate;
        return *this;
    }

    Actor(const Actor& other)
            : nume(other.nume), varsta(other.varsta), filmeJucate(other.filmeJucate)
    {}

    ~Actor(){}

    friend std::ostream& operator<<(std::ostream& os, const Actor& other) {
        os << other.nume << ", " << other.varsta << " ani ";
        os << "[filme in care joaca: ";
        for (auto it = other.filmeJucate.begin(); it != other.filmeJucate.end(); ++it) {
            os << *it;
            if (it != other.filmeJucate.end() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    std::string getNume() const {
        return nume;
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

    void afisFilme(const std::vector<Film>& filme) {
        for (const Film& film : filme) {
            std::cout << film << std::endl;
        }
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
        balanta.adaugaSuma(sumaAdaugata);
    }

    bool areBani(int pretBilet) const {
        return balanta.getSuma() >= pretBilet;
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
        Actor brad("Brad Pitt", 60, {"Once Upon a Time... in Hollywood", "Fight Club", "Fury"});
        Actor leo("Leonardo DiCaprio", 49, {"The Wolf Of Wallstreet", "The Departed", "Once Upon a Time... in Hollywood"});
        Actor matt("Matt Damon", 53, {"Good Will Hunting", "Oppenheimer"});

        Film hollywood("Once Upon A Time... in Hollywood", 162, 15, {brad, leo});
        Film fight("Fight Club", 139, 20, {brad});
        Film fury("Fury", 135, 18, {brad});
        Film wolf("The Wolf Of Wallstreet", 180, 20, {leo});
        Film departed("The Departed", 151, 25, {matt, leo});
        Film will("Good Will Hunting", 127, 19,{matt});
        Film opp("Oppenheimer", 181, 23, {matt});

        filme.push_back(hollywood);
        filme.push_back(fight);
        filme.push_back(fury);
        filme.push_back(wolf);
        filme.push_back(departed);
        filme.push_back(will);
        filme.push_back(opp);
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
                user.adaugaInBalanta(-filme[numar_selectat - 1].getPret());
                std::cout << "Balanta curenta: " << user.getBalanta() << "\n";
            } else {
                std::cout << "Nu ai suficienti bani pentru a cumpara biletul.\n";
            }
        }
    }

    void selectareCategorie() {
        std::cout << "Esti student sau pensionar? [y/n]";
        std::string raspuns;
        std::cin >> raspuns;
        if (raspuns == "y") {
            user.setCategorie(true);
            std::cout << "Beneficiezi de reduceri la filmele care sunt mai scumpe de 20 RON!\n";
        } else {
            user.setCategorie(false);
            std::cout << "Nu beneficiezi de reducere.\n";
        }
    }

    void manageriereBalanta() {
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

    bool ok = true;
    while(ok) {
        std::cout << "Alegi ce vrei sa faci:\n1. Alege un film\n2. Actualizeaza categoria\n3. Gestioneaza balata\n"; //urmeaza sa fie adaugate mai multe lucruri (adauga o metoda de plata, schimba cinema-ul etc.)
        std::cout << "[Introdu un numar]:";
        std::string alegere;
        std::cin >> alegere;
        std::cout << '\n';

        if (alegere == "1") {
            app.cumparaBiletFilm();
        } else if (alegere == "2") {
            app.selectareCategorie();
        }
        else if (alegere == "3") {
            app.manageriereBalanta();
        }
        std::cout << "\nDoresti sa mai faci ceva? [y/n]";
        std::cin >> alegere;
        std::cout << "\n";
        if(alegere == "y"){
            ok = true;
        }
        else{
            ok = false;
        }
    }

    return 0;
}


//vor mai fi adaugate clase cu sali, locuri, functii pentru adaugat filme, pentru schimbarea locului
