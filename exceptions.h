#pragma once

#include <iostream>

class NotSufficientElements : public std::exception
{
public:
    const char *what() const throw() override
    {
        return const_cast<char *>("Not sufficient elements in database to run quiz!");
    }
};

class WordNotFound : public std::exception
{
private:
    std::string word{""};
public:
    WordNotFound(const string &word) : std::exception(), word(word) {}
    const char *what() const throw() override {
        std::string aux = "Word " + word + " not found in database!";
        return aux.c_str();
    }
};