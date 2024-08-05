#include <iostream>
#include "entity.h"

using namespace std;

entity::entity(const entity &other) {
    word = other.word;
    meaning = other.meaning;
    p = new short int{*(other.p)};
}

entity::~entity() {
    delete p;
}

std::string entity::get_word() const {
    return word;
}

std::string entity::get_meaning() const {
    return meaning;
}

short int entity::get_lives() const {
    return *p;
}

void entity::decrement_lives() const {
    *p = (*p) - 1;
}

bool operator <(const entity &left, const entity &right) {
    return left.get_word() < right.get_word();
}
