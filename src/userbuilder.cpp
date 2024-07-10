#include "../Headers/userbuilder.h"

UserBuilder::UserBuilder()
        : username(""), parola(""), salt(""), balanta(0), categorie(false), role("") {}

UserBuilder& UserBuilder::setUsername(const std::string& username) {
    this->username = username;
    return *this;
}

UserBuilder& UserBuilder::setParola(const std::string& parola) {
    this->parola = parola;
    return *this;
}

UserBuilder& UserBuilder::setSalt(const std::string& salt) {
    this->salt = salt;
    return *this;
}

UserBuilder& UserBuilder::setBalanta(const Balanta& balanta) {
    this->balanta = balanta;
    return *this;
}

UserBuilder& UserBuilder::setCategorie(bool categorie) {
    this->categorie = categorie;
    return *this;
}

UserBuilder& UserBuilder::setRole(const std::string& role) {
    this->role = role;
    return *this;
}

User UserBuilder::build() {
    return User(username, parola, salt, balanta, categorie, role);
}
