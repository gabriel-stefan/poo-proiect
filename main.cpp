#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <digestpp.hpp>
//#include <functional>
//#include <thread>
//#include <SFML/Graphics.hpp>
//#include <Helper.h>
//#include "env_fixes.h"
#include "passwordmanager.h"
#include "film.h"
#include "user.h"
#include "aplicatie.h"


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

