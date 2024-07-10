#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "Headers/passwordmanager.h"
#include "Headers/film.h"
#include "Headers/user.h"
#include "Headers/aplicatie.h"

int main() {
    try {
        Aplicatie& app = Aplicatie::getInstance();

        bool autentificat = false;
        while (!autentificat) {
            std::cout << "1. Creeaza cont nou\n";
            std::cout << "2. Conecteaza-te\n";
            std::cout << "3. Iesi\n";
            std::cout << "Alege o optiune: ";
            int optiune;
            std::cin >> optiune;

            try {
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
            } catch (const UserAlreadyExistsException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            } catch (const InvalidChoiceException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            } catch (const CustomException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            } catch (const std::exception& e) {
                std::cout << "A aparut o eroare neasteptata: " << e.what() << "\n";
            }
        }

        app.meniuUtilizator();
    } catch (const std::exception& e) {
        std::cout << "A aparut o eroare neasteptata: " << e.what() << "\n";
    }

    return 0;
}
