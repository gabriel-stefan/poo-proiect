#ifndef OOP_CARD_H
#define OOP_CARD_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include "paymentMethod.h"
#include "passwordmanager.h"
#include "exceptieCustom.h"

class InvalidCardNumberException : public CustomException {
public:
    explicit InvalidCardNumberException();
};

class InsufficientFundsException : public CustomException {
public:
    explicit InsufficientFundsException();
};

class InvalidCVVException : public CustomException {
public:
    explicit InvalidCVVException();
};

class Card : public PaymentMethod {
private:
    std::string nume;
    std::string hashedNumarCard;
    std::string dataExpirare;
    std::string hashedCVV;
    std::unordered_map<std::string, int> testCardNumbers;
    const std::string validCVV;

public:
    Card();
    Card(const std::string &nume, const std::string &numarCard, const std::string &dataExpirare, const std::string &cvv);

    void pay(int suma) const override;
    std::unique_ptr<PaymentMethod> clone() const override;
};

#endif // OOP_CARD_H