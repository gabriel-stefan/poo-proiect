#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <stdexcept>
#include <string>

class CustomException : public std::runtime_error {
public:
    explicit CustomException(const std::string &message)
            : std::runtime_error(message) {}
};

#endif // CUSTOM_EXCEPTION_H
