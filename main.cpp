#include <iostream>
#include <vector>
#include <chrono>
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
    {
        nume = other.nume;
        varsta = other.varsta;
    }

    ~Actor(){}

    friend std::ostream& operator<<(std::ostream& os, const Actor& other) {
        os << other.nume;
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
    {
        nume = other.nume;
        durata = other.durata;
        cast = other.cast;
        pret = other.pret;
    }

    ~Film(){}

    friend std::ostream& operator<<(std::ostream& os, const Film& other) {
        os << "Nume film: " << other.nume << ", Durata: " << other.durata << ", Pret: " << other.pret << "\n";
        os << "Actori: ";
        for (const Actor& actor : other.cast) {
            os << actor << ", ";
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
    {
        suma = other.suma;
    }

    ~Balanta(){}

    friend std::ostream& operator<<(std::ostream& os, const Balanta& other) {
        os << "Balanta: " << other.suma << "\n";
        return os;
    }

    int getBalanta() const {
        return suma;
    }

};

class User{
private:
    std::string username;
    std::string parola;
    Balanta balanta;
    std::string categorie;
public:
    User() = default;

    User(const std::string& _username, const std::string& _parola, const Balanta& _balanta, const std::string& _categorie)
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
    {
        username = other.username;
        parola = other.parola;
        balanta = other.balanta;
        categorie = other.categorie;
    }

    ~User(){}

    friend std::ostream& operator<<(std::ostream& os, const User& other) {
        os << "Username: " << other.username << ", Parola: " << other.parola << "\n" << other.balanta;
        return os;
    }

    void setUsername(const std::string& usernameNou) {
        username = usernameNou;
    }

    void setPassword(const std::string& parolaNoua) {
        parola = parolaNoua;
    }

    bool checkLogin(const std::string& _username, const std::string& _parola) {
        return ("admin" == _username && "parola123" == _parola);
    }

    void reducere(Film& film) {
        if (categorie == "student" && film.getPret() > 20) {
            film.setPret(15);
            std::cout << "Biletul a fost redus la 15 lei deoarece esti student." << std::endl;
        }
    }

};



int main() {

    User prim("admin","parola123", 150, "student");
    std::cout << "Conectare\n" << "Username:";
    std::string username, parola;
    std::cin >> username;
    std::cout << "Parola:";
    std::cin >> parola;
    prim.setUsername(username);   //username-ul e admin si parola parola123
    prim.setPassword(parola);
    bool valid =  prim.checkLogin(username, parola);

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

    std::vector<Film> films;

    films.push_back(hollywood);
    films.push_back(fight);
    films.push_back(fury);
    films.push_back(wolf);
    films.push_back(departed);
    films.push_back(will);
    films.push_back(opp);

    if(valid == 0) {
        std::cout << "Datele de conectare nu sunt corecte!";
    }
    else {
        std::cout << "Te-ai conectat cu succes!\n\n";
        std::cout << "Alegi ce vrei sa faci:\n1. Alege un film\n\n"; //urmeaza sa fie adaugate mai multe lucruri (adauga o metoda de plata, schimba cinema-ul etc.)

        for (size_t i = 0; i < films.size(); ++i) {
            std::cout << i + 1 << ". " << films[i] << "\n\n";
        }

        size_t nr = films.size();

        std::cout << "Alege un film pentru care vrei sa cumperi bilet:\n";

        size_t numar_selectat;
        std::cin >> numar_selectat;

        if(numar_selectat > nr) {
            std::cout << "Ai ales un numar prea mare care nu corespunde niciunui film!\n";
            return 0;
        }
        else{
            prim.reducere(films[numar_selectat-1]);
            std::cout << "Felicitari! Ai cumparat bilet!\n";  //mai trebuie verificat daca sunt bani suficienti si un update la balanta
        }
    }
    return 0;
}


//vor mai fi adaugate clase cu sali, locuri, functii pentru adaugat filme, pentru schimbarea locului
