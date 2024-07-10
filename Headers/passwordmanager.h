#ifndef OOP_PASSWORDMANAGER_H
#define OOP_PASSWORDMANAGER_H

#include <string>
#include <cstdint>

class PasswordManager {
public:
    static std::string make_salt();
    static std::string hash_password(const std::string& plain, const std::string& salt);
private:
    static uint64_t get_next_salt();
    static void update_salt(uint64_t new_salt);
};

#endif //OOP_PASSWORDMANAGER_H
