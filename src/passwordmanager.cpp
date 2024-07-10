//
// Created by Gabriel on 6/30/2024.
//

#include "../Headers/passwordmanager.h"
#include "digestpp.hpp"

std::string PasswordManager::make_salt() {
    static uint64_t nr = 1u;
    std::string salt;
    auto bytes = static_cast<char*>(static_cast<void*>(&nr));
    for(unsigned i = 0; i < 16; i++) {
        salt += bytes[i % 8];
    }
    ++nr;
    return salt;
}

std::string PasswordManager::hash_password(const std::string& plain, const std::string& salt) {
    return digestpp::blake2b(512).set_salt(salt).absorb(plain).hexdigest();
}