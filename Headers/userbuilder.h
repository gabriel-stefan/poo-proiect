#ifndef USERBUILDER_H
#define USERBUILDER_H

#include <string>
#include "balanta.h"
#include "user.h"

class UserBuilder {
public:
    UserBuilder();

    UserBuilder& setUsername(const std::string& username);
    UserBuilder& setParola(const std::string& parola);
    UserBuilder& setSalt(const std::string& salt);
    UserBuilder& setBalanta(const Balanta& balanta);
    UserBuilder& setCategorie(bool categorie);
    UserBuilder& setRole(const std::string& role);

    User build();

private:
    std::string username;
    std::string parola;
    std::string salt;
    Balanta balanta;
    bool categorie;
    std::string role;
};

#endif //USERBUILDER_H
