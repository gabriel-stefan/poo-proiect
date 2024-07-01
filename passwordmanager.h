//
// Created by Gabriel on 6/30/2024.
//

#include <string>  // include string pentru a folosi std::string
#include "digestpp.hpp"

#ifndef OOP_PASSWORDMANAGER_H
#define OOP_PASSWORDMANAGER_H


class PasswordManager {
public:
    static std::string make_salt() {
        static uint64_t nr = 1u;
        std::string salt;
        auto bytes = static_cast<char*>(static_cast<void*>(&nr));
        for(unsigned i = 0; i < 16; i++) {
            salt += bytes[i%8];
        }
        ++nr;
        return salt;
    }

    static std::string hash_password(const std::string& plain, const std::string& salt) {
        return digestpp::blake2b(512).set_salt(salt).absorb(plain).hexdigest();
    }
};

#endif //OOP_PASSWORDMANAGER_H