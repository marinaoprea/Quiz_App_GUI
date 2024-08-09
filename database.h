#ifndef DATABASE_H
#define DATABASE_H

#include <set>
#include <vector>
#include <utility>
#include "entity.h"

class database {
private:
    set<entity> data;
    int last_save{0};

public:
    database() = default;
    void load();
    string add_word(const string &word, const string &meaning);
    void dump_to_file(const string &filename) const;

    string search_meaning(const string &word) const;
    vector<string> get_quiz_questions()const;
    bool check(const string &word, const string &meaning) const;
    bool decrement_lives(const string &word);
    void erase_word(const string &word);
};

#endif