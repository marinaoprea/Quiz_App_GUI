#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <memory>

#include "constants.h"

using namespace std;

class entity
{
private:
    string word{""};
    string meaning{""};
    // short int lives{INITIAL_WORD_LIVES};
    short int *p;

public:
    entity(string word, string meaning) : word(word), meaning(meaning) { p = new short int{INITIAL_WORD_LIVES}; }
    entity(string word, string meaning, short int lives) : word(word), meaning(meaning) { p = new short int{lives}; }
    entity(const entity &other);
    ~entity();
    string get_word() const;
    string get_meaning() const;
    short int get_lives() const;
    void decrement_lives() const;
};

bool operator<(const entity &left, const entity &right);

#endif