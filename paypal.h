//
// Created by Gabriel on 7/7/2024.
//

#ifndef OOP_PAYPAL_H
#define OOP_PAYPAL_H

#include "paymentMethod.h"
#include "passwordManager.h"
#include "exceptieCustom.h"
#include <iostream>
#include <memory>

class InvalidPayPalCredentialsException : public CustomException {
public:
    InvalidPayPalCredentialsException() : CustomException("Invalid PayPal credentials. Error: 1000001") {}
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

    void pay(int suma) const override {
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
    }

    std::unique_ptr<PaymentMethod> clone() const override {
        return std::make_unique<PayPal>(*this);
    }
};


#endif //OOP_PAYPAL_H
