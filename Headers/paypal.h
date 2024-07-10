//
// Created by Gabriel on 7/7/2024.
//

#ifndef OOP_PAYPAL_H
#define OOP_PAYPAL_H

#include "paymentMethod.h"
#include "passwordmanager.h"
#include "exceptieCustom.h"
#include <iostream>
#include <memory>

class InvalidPayPalCredentialsException : public CustomException {
public:
    InvalidPayPalCredentialsException();
};

class PayPal : public PaymentMethod {
private:
    std::string email;
    std::string hashedParola;
    std::string salt;

    const std::string validEmail;
    const std::string validHashedParola;
    const std::string validSalt;

public:
    PayPal();
    PayPal(const std::string &email, const std::string &parola);

    void pay(int suma) const override;
    std::unique_ptr<PaymentMethod> clone() const override;
};

#endif //OOP_PAYPAL_H