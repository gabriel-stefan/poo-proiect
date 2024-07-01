#ifndef OOP_BALANTA_H
#define OOP_BALANTA_H

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "passwordmanager.h"

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool pay(int suma) const = 0;
    virtual std::unique_ptr<PaymentMethod> clone() const = 0;

    PaymentMethod() = default;
    PaymentMethod(const PaymentMethod&) = default;
    PaymentMethod(PaymentMethod&&) = default;
    PaymentMethod& operator=(const PaymentMethod&) = default;
    PaymentMethod& operator=(PaymentMethod&&) = default;
};

class InvalidCardNumberException : public std::runtime_error {
public:
    InvalidCardNumberException() : std::runtime_error("Invalid card number. Error: 1000001") {}
};

class InsufficientFundsException : public std::runtime_error {
public:
    InsufficientFundsException() : std::runtime_error("Insufficient funds. Error: 1000002") {}
};

class InvalidCVVException : public std::runtime_error {
public:
    InvalidCVVException() : std::runtime_error("Invalid CVV. Error: 1000004") {}
};

class InvalidPayPalCredentialsException : public std::runtime_error {
public:
    InvalidPayPalCredentialsException() : std::runtime_error("Invalid PayPal credentials. Error: 1000001") {}
};

class Card : public PaymentMethod {
private:
    std::string nume;
    std::string hashedNumarCard;
    std::string dataExpirare;
    std::string hashedCVV;

    std::unordered_map<std::string, int> testCardNumbers = {
            {"4242424242424242", 0},  // Successful purchase
            {"4242424242424241", 1000001},  // Invalid card number
            {"4242424242000089", 1000002}  // Insufficient funds
    };
    const std::string validCVV = "123";  // Only valid CVV

public:
    Card() = default;

    Card(const std::string &nume, const std::string &numarCard, const std::string &dataExpirare, const std::string &cvv)
            : nume(nume), dataExpirare(dataExpirare) {
        hashedNumarCard = PasswordManager::hash_password(numarCard, PasswordManager::make_salt());
        hashedCVV = PasswordManager::hash_password(cvv, PasswordManager::make_salt());
    }

    bool pay(int suma) const override {
        std::string nume;
        std::string numarCard;
        std::string dataExpirare;
        std::string cvv;

        std::cout << "Introdu numele de pe card: ";
        std::cin.ignore();
        std::getline(std::cin, nume);
        std::cout << "Introdu numarul cardului: ";
        std::cin.ignore();
        std::getline(std::cin, numarCard);
        std::cout << "Introdu data expirarii (MM/YY): ";
        std::cin.ignore();
        std::getline(std::cin, dataExpirare);
        std::cout << "Introdu CVV-ul: ";
        std::cin.ignore();
        std::getline(std::cin, cvv);

        std::string hashedNumarCardInput = PasswordManager::hash_password(numarCard, PasswordManager::make_salt());
        std::string hashedCVVInput = PasswordManager::hash_password(cvv, PasswordManager::make_salt());

        auto it = testCardNumbers.find(numarCard);
        if (it == testCardNumbers.end()) {
            throw InvalidCardNumberException();
        } else if (it->second == 1000002) {
            throw InsufficientFundsException();
        }

        if (cvv != validCVV) {
            throw InvalidCVVException();
        }

        std::cout << "Plata cu cardul a fost efectuata cu succes!\n";
        return true;
    }

    std::unique_ptr<PaymentMethod> clone() const override {
        return std::make_unique<Card>(*this);
    }
};

class PayPal : public PaymentMethod {
private:
    std::string email;
    std::string hashedParola;

    const std::string validEmail = "test123@gmail.com";
    const std::string validParola = "parola123";

public:
    PayPal() = default;

    PayPal(const std::string &email, const std::string &parola)
            : email(email) {
        hashedParola = PasswordManager::hash_password(parola, PasswordManager::make_salt());
    }

    bool pay(int suma) const override {
        std::string email;
        std::string parola;

        std::cout << "Introdu email-ul contului PayPal: ";
        std::cin.ignore();
        std::getline(std::cin, email);
        std::cout << "Introdu parola contului PayPal: ";
        std::getline(std::cin, parola);

        std::string hashedParolaInput = PasswordManager::hash_password(parola, PasswordManager::make_salt());

        if (email != validEmail || parola != validParola) {
            throw InvalidPayPalCredentialsException();
        }

        std::cout << "Plata cu PayPal a fost efectuata cu succes!\n";
        return true;
    }

    std::unique_ptr<PaymentMethod> clone() const override {
        return std::make_unique<PayPal>(*this);
    }
};

class Balanta{
private:
    int suma;
    std::unique_ptr<PaymentMethod> paymentMethod;
public:
    Balanta() = default;

    explicit Balanta(const int _suma)
            :suma(_suma)
    {}

    Balanta& operator=(const Balanta& other) {
        if (this != &other) {
            suma = other.suma;
            if (other.paymentMethod) {
                paymentMethod = other.paymentMethod->clone();
            } else {
                paymentMethod.reset();
            }
        }
        return *this;
    }

    Balanta(const Balanta& other)
            : suma(other.suma), paymentMethod(nullptr)
    {
        if (other.paymentMethod) {
            paymentMethod = other.paymentMethod->clone();
        }
    }

    Balanta(Balanta&& other) = default;
    Balanta& operator=(Balanta&& other) = default;

    int getSuma() const {
        return suma;
    }

    ~Balanta(){}

    void adaugaSuma(int sumaAdaugata) {
        suma += sumaAdaugata;
    }

    void setPaymentMethod(std::unique_ptr<PaymentMethod> method) {
        paymentMethod = std::move(method);
    }

    bool pay(int amount) const {
        if (paymentMethod) {
            try {
                return paymentMethod->pay(amount);
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
                return false;
            }
        } else {
            std::cout << "No payment method set." << std::endl;
            return false;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Balanta& other) {
        os << "Balanta: " << other.suma << "\n";
        return os;
    }

};

#endif // OOP_BALANTA_H
