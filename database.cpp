#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "nlohmann/json.hpp"
#include "helper.h"
#include "database.h"
#include "entity.h"
#include "exceptions.h"

using json = nlohmann::json;

void database::load()
{
    ifstream fin(DATABASE_PATH);

    json j_arr = json::parse(fin);
    for (auto elem : j_arr)
    {
        data.emplace(entity(elem[WORD], elem[MEANING], elem[LIVES]));
    }

    fin.close();
}

string database::add_word(const string &word, const string &meaning)
{
    auto elem = entity(word, meaning);
    auto it = data.find(elem);

    if (it != data.end())
    {
        return "Word " + word + "already exists with meaning " + it->get_meaning();
    }

    data.insert(entity(word, meaning));
    return "Added new word";
}

void database::dump_to_file(const string &filename) const
{
    ofstream fout(filename);
    json j_arr;

    for (auto &entry : data)
    {
        json elem;
        elem[WORD] = entry.get_word();
        elem[MEANING] = entry.get_meaning();
        elem[LIVES] = entry.get_lives();

        j_arr.push_back(elem);
    }

    fout << j_arr.dump(4);
}

void database::search_word() const
{
    std::cout << "Insert word:";
    std::string word;

    std::cin.get();
    std::getline(std::cin, word);

    entity aux = entity(word, "");

    auto it = data.find(aux);
    if (it == data.end())
        std::cout << "Word " + word + " does not exist!\n";
    else
        std::cout << it->get_word() + " = " + it->get_meaning() + "\n";
}

void database::delete_word()
{
    std::cout << "Insert word:";
    std::string word;

    std::cin.get();
    std::getline(std::cin, word);

    entity aux = entity(word, "");

    auto it = data.find(aux);
    if (it == data.end())
    {
        std::cout << "Word " + word + " does not exist!\n";
    }
    else
    {
        data.erase(*it);
        std::cout << "Deleted word " + word + ".\n";
    }

    // modify_check();
}

vector<string> database::get_quiz_questions() const
{
    vector<const entity *> aux;
    vector<string> ans;
    random_device rd;
    mt19937 mt(rd());

    for (auto &elem : data)
        aux.push_back(&elem);

    if (aux.size() < NO_QUESTIONS)
        throw NotSufficientElements();

    uniform_int_distribution<int> idist(0, aux.size() - 1);

    for (auto i = 0; i < NO_QUESTIONS; i++)
    {
        auto index = idist(mt);
        auto elem = aux.at(index);
        auto word = elem->get_word();
        auto it = find(ans.begin(), ans.end(), word);
        if (it == ans.end())
            ans.push_back(elem->get_word());
        else
            i--;
    }

    return ans;
}

bool database::check(const string &word, const string &meaning) const
{
    auto elem = entity(word, "");
    auto it = data.find(elem);
    if (it == data.end())
        return false;

    return it->get_meaning() == meaning;
}

bool database::decrement_lives(const string &word)
{
    auto elem = entity(word, "");
    auto it = data.find(elem);
    if (it == data.end())
        return false;

    if (it->get_lives() == 1)
        return true;

    it->decrement_lives();
    return false;
}

void database::erase_word(const string &word)
{
    data.erase(entity(word, ""));
}

string database::search_meaning(const string &word) const
{
    auto it = data.find(entity(word, ""));
    if (it == data.end()) {
        throw WordNotFound(word);
    }

    return it->get_meaning();
}