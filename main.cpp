#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <digestpp.hpp>
#include "passwordmanager.h"
#include "film.h"
#include "user.h"
#include "aplicatie.h"

int main() {
    Aplicatie app;
    app.initializareFilme();

    bool autentificat = false;
    while (!autentificat) {
        std::cout << "1. Creeaza cont nou\n";
        std::cout << "2. Conecteaza-te\n";
        std::cout << "3. Iesi\n";
        std::cout << "Alege o optiune: ";
        int optiune;
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                app.signUp();
                break;
            case 2:
                autentificat = app.logIn();
                if (!autentificat) {
                    std::cout << "Datele de autentificare nu sunt corecte.\n";
                }
                break;
            case 3:
                return 0;
            default:
                std::cout << "Optiune invalida.\n";
                break;
        }
    }

    app.meniuUtilizator();

    return 0;
}
