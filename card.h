#ifndef OOP_CARD_H
#define OOP_CARD_H

#include <iostream>
#include "paymentMethod.h"
#include "passwordManager.h"
#include <unordered_map>
#include "exceptieCustom.h"
#include <memory>

class InvalidCardNumberException : public CustomException {
public:
    InvalidCardNumberException() : CustomException("Invalid card number. Error: 1000001") {}
};

class InsufficientFundsException : public CustomException {
public:
    InsufficientFundsException() : CustomException("Insufficient funds. Error: 1000002") {}
};

class InvalidCVVException : public CustomException {
public:
    InvalidCVVException() : CustomException("Invalid CVV. Error: 1000004") {}
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

    void pay(int suma) const override {
        std::string inputNume;
        std::string inputNumarCard;
        std::string inputDataExpirare;
        std::string inputCVV;

        std::cout << "Introdu numele de pe card: ";
        std::cin.ignore();
        std::getline(std::cin, inputNume);
        std::cout << "Introdu numarul cardului: ";
        std::getline(std::cin, inputNumarCard);
        std::cout << "Introdu data expirarii (MM/YY): ";
        std::getline(std::cin, inputDataExpirare);
        std::cout << "Introdu CVV-ul: ";
        std::getline(std::cin, inputCVV);

        auto it = testCardNumbers.find(inputNumarCard);
        if (it == testCardNumbers.end()) {
            throw InvalidCardNumberException();
        } else if (it->second == 1000002) {
            throw InsufficientFundsException();
        }

        if (inputCVV != validCVV) {
            throw InvalidCVVException();
        }

        std::cout << "Plata cu cardul a fost efectuata cu succes!\n";
    }

    std::unique_ptr<PaymentMethod> clone() const override {
        return std::make_unique<Card>(*this);
    }
};

#endif //OOP_CARD_H
