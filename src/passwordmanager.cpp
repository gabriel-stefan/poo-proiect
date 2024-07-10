#include "../Headers/passwordmanager.h"
#include "digestpp.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

uint64_t PasswordManager::get_next_salt() {
    std::ifstream in("salt_max.txt");
    uint64_t current_salt = 1;
    if (in.is_open()) {
        in >> current_salt;
        in.close();
    }
    return current_salt;
}

void PasswordManager::update_salt(uint64_t new_salt) {
    std::ofstream out("salt_max.txt");
    if (out.is_open()) {
        out << new_salt;
        out.close();
    } else {
        throw std::runtime_error("Nu se poate deschide salt_max.txt.");
    }
}

std::string PasswordManager::make_salt() {
    uint64_t current_salt = get_next_salt();
    update_salt(current_salt + 1);

    std::string salt;
    auto bytes = reinterpret_cast<char*>(&current_salt);
    for (unsigned i = 0; i < 8; i++) {
        salt += bytes[i];
    }
    salt += salt;

    return salt;
}

std::string PasswordManager::hash_password(const std::string& plain, const std::string& salt) {
    return digestpp::blake2b(512).set_salt(salt).absorb(plain).hexdigest();
}
