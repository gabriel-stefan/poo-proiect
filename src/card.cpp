#include "../Headers/card.h"
#include "../Headers/passwordmanager.h"

InvalidCardNumberException::InvalidCardNumberException()
        : CustomException("Invalid card number. Error: 1000001") {}

InsufficientFundsException::InsufficientFundsException()
        : CustomException("Insufficient funds. Error: 1000002") {}

InvalidCVVException::InvalidCVVException()
        : CustomException("Invalid CVV. Error: 1000004") {}

Card::Card()
        : nume(""), hashedNumarCard(""), dataExpirare(""), hashedCVV(""), testCardNumbers({
                                                                                                  {"4242424242424242", 0},  // Successful purchase
                                                                                                  {"4242424242424241", 1000001},  // Invalid card number
                                                                                                  {"4242424242000089", 1000002}  // Insufficient funds
                                                                                          }), validCVV("123") {}

Card::Card(const std::string &nume, const std::string &numarCard, const std::string &dataExpirare, const std::string &cvv)
        : nume(nume), hashedNumarCard(PasswordManager::hash_password(numarCard, PasswordManager::make_salt())),
          dataExpirare(dataExpirare), hashedCVV(PasswordManager::hash_password(cvv, PasswordManager::make_salt())),
          testCardNumbers({
                                  {"4242424242424242", 0},  // Successful purchase
                                  {"4242424242424241", 1000001},  // Invalid card number
                                  {"4242424242000089", 1000002}  // Insufficient funds
                          }), validCVV("123") {}

void Card::pay(int ) const {
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

std::unique_ptr<PaymentMethod> Card::clone() const {
    return std::make_unique<Card>(*this);
}