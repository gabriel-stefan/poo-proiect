#ifndef OOP_PASSWORDMANAGER_H
#define OOP_PASSWORDMANAGER_H

#include <string>  // include string pentru a folosi std::string

class PasswordManager {
public:
    static std::string make_salt();
    static std::string hash_password(const std::string& plain, const std::string& salt);
};

#endif //OOP_PASSWORDMANAGER_H
