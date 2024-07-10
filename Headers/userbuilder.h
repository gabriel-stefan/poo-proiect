#ifndef OOP_USERBUILDER_H
#define OOP_USERBUILDER_H

#include "user.h"

class UserBuilder {
private:
    std::string username;
    std::string parola;
    std::string salt;
    Balanta balanta;
    bool categorie;
    std::string role;

public:
    UserBuilder& setUsername(const std::string& username);
    UserBuilder& setParola(const std::string& parola);
    UserBuilder& setSalt(const std::string& salt);
    UserBuilder& setBalanta(const Balanta& balanta);
    UserBuilder& setCategorie(bool categorie);
    UserBuilder& setRole(const std::string& role);
    User build();
};

#endif // OOP_USERBUILDER_H
