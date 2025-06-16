#pragma once
#include "String.h"
#include <exception>

class InsufficientBalanceException : public std::exception {
public:
    const char* what() const noexcept override;
};