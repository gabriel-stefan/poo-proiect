#include "../Headers/balanta.h"
#include "../Headers/paymentMethod.h"
#include "../Headers/exceptieCustom.h"
#include <iostream>


Balanta::Balanta() : suma(0) {}

Balanta::Balanta(const int _suma) : suma(_suma) {}

Balanta& Balanta::operator=(const Balanta& other) {
    if (this != &other) {
        suma = other.suma;
        transactionHistory = other.transactionHistory;
        if (other.paymentMethod) {
            paymentMethod = other.paymentMethod->clone();
        } else {
            paymentMethod.reset();
        }
    }
    return *this;
}

Balanta::Balanta(const Balanta& other)
        : suma(other.suma), transactionHistory(other.transactionHistory), paymentMethod(nullptr) {
    if (other.paymentMethod) {
        paymentMethod = other.paymentMethod->clone();
    }
}

Balanta::~Balanta() {}

int Balanta::getSuma() const {
    return suma;
}

void Balanta::adaugaSuma(int sumaAdaugata) {
    suma += sumaAdaugata;
    transactionHistory.push_back(sumaAdaugata);
}

void Balanta::scadeSuma(int sumaScazuta) {
    if (sumaScazuta > suma) {
        //throw InsufficientFundsException();
    }
    suma -= sumaScazuta;
    transactionHistory.push_back(-sumaScazuta);
}


void Balanta::pay(int amount) const {
    if (paymentMethod) {
        paymentMethod->pay(amount);
    } else {
        std::cout << "No payment method set." << std::endl;
    }
}

void Balanta::afisareIstoricTranzactii() const {
    std::cout << "Istoric tranzactii:\n";
    for (const auto& tranzactie : transactionHistory) {
        std::cout << tranzactie << " lei\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Balanta& other) {
    os << "Balanta: " << other.suma << "\n";
    return os;
}