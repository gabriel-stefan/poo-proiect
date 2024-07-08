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
    std::string salt;

    const std::string validEmail = "test123@gmail.com";
    const std::string validHashedParola = PasswordManager::hash_password("parola123", "fixed_salt");
    const std::string validSalt = "fixed_salt";

public:
    PayPal() = default;

    PayPal(const std::string &email, const std::string &parola)
            : email(email), salt(PasswordManager::make_salt()) {
        hashedParola = PasswordManager::hash_password(parola, salt);
    }

    void pay(int suma) const override {
        std::string emailInput;
        std::string parolaInput;

        std::cout << "Introdu email-ul contului PayPal: ";
        std::cin.ignore();
        std::getline(std::cin, emailInput);
        std::cout << "Introdu parola contului PayPal: ";
        std::getline(std::cin, parolaInput);

        std::string hashedParolaInput = PasswordManager::hash_password(parolaInput, validSalt);

        if (emailInput != validEmail || hashedParolaInput != validHashedParola) {
            throw InvalidPayPalCredentialsException();
        }

        std::cout << "Plata cu PayPal a fost efectuata cu succes!\n";
    }

    std::unique_ptr<PaymentMethod> clone() const override {
        return std::make_unique<PayPal>(*this);
    }
};

#endif //OOP_PAYPAL_H
