#include "../Headers/paypal.h"

InvalidPayPalCredentialsException::InvalidPayPalCredentialsException()
        : CustomException("Invalid PayPal credentials. Error: 1000001") {}

PayPal::PayPal()
        : validEmail("test123@gmail.com"),
          validHashedParola(PasswordManager::hash_password("parola123", "fixed_salt")),
          validSalt("fixed_salt") {}

PayPal::PayPal(const std::string &email, const std::string &parola)
        : email(email),
          salt(PasswordManager::make_salt()),
          validEmail("test123@gmail.com"),
          validHashedParola(PasswordManager::hash_password("parola123", "fixed_salt")),
          validSalt("fixed_salt") {
    hashedParola = PasswordManager::hash_password(parola, salt);
}

void PayPal::pay(int) const {
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

std::unique_ptr<PaymentMethod> PayPal::clone() const {
    return std::make_unique<PayPal>(*this);
}
