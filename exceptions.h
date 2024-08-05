#pragma once

#include <iostream>

class NotSufficientElements : public std::exception {
public:
    const char *what() const throw () override {
        return const_cast<char *>("Not sufficient elements in database to run quiz!");
    }
};