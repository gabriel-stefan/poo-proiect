#ifndef OOP_BALANTA_H
#define OOP_BALANTA_H

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include "passwordmanager.h"
#include "exceptieCustom.h"
#include "paymentMethod.h"
#include "paypal.h"
#include "card.h"


class Balanta {
private:
    int suma;
    std::vector<int> transactionHistory;
    std::unique_ptr<PaymentMethod> paymentMethod;

public:
    Balanta() : suma(0) {}

    explicit Balanta(const int _suma)
            : suma(_suma) {}

    Balanta& operator=(const Balanta& other) {
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

    Balanta(const Balanta& other)
            : suma(other.suma), transactionHistory(other.transactionHistory), paymentMethod(nullptr) {
        if (other.paymentMethod) {
            paymentMethod = other.paymentMethod->clone();
        }
    }

    Balanta(Balanta&& other) = default;
    Balanta& operator=(Balanta&& other) = default;

    int getSuma() const {
        return suma;
    }

    ~Balanta() {}

    void adaugaSuma(int sumaAdaugata) {
        suma += sumaAdaugata;
        transactionHistory.push_back(sumaAdaugata);
    }

    void scadeSuma(int sumaScazuta) {
        if (sumaScazuta > suma) {
            throw InsufficientFundsException();
        }
        suma -= sumaScazuta;
        transactionHistory.push_back(-sumaScazuta);
    }

    void setPaymentMethod(std::unique_ptr<PaymentMethod> method) {
        paymentMethod = std::move(method);
    }

    void pay(int amount) const {
        if (paymentMethod) {
            paymentMethod->pay(amount);
        } else {
            std::cout << "No payment method set." << std::endl;
        }
    }

    void afisareIstoricTranzactii() const {
        std::cout << "Istoric tranzactii:\n";
        for (const auto& tranzactie : transactionHistory) {
            std::cout << tranzactie << " lei\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Balanta& other) {
        os << "Balanta: " << other.suma << "\n";
        return os;
    }
};

#endif // OOP_BALANTA_H
