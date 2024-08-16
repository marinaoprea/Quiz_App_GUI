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
        return "Word " + word + " already exists with meaning " + it->get_meaning() + ".";
    }

    data.insert(entity(word, meaning));
    return "Added " + word + " = " + meaning;
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

int database::check(const string &word, const string &meaning) const
{
    auto elem = entity(word);
    auto it = data.find(elem);
    if (it == data.end())
        return 1e9;

    return levenstein(it->get_meaning(), meaning);
}

bool database::decrement_lives(const string &word)
{
    auto elem = entity(word);
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
    auto elem = entity(word);
    auto it = data.find(elem);
    if (it == data.end())
        throw WordNotFound(word);
    data.erase(elem);
}

string database::search_meaning(const string &word) const
{
    auto it = data.find(entity(word));
    if (it == data.end())
    {
        throw WordNotFound(word);
    }

    return it->get_meaning();
}

vector<string> database::search_contains(const string &word) const
{
    vector<string> ans;
    for (auto elem : data)
        if (elem.get_word().find(word) != elem.get_word().npos)
            ans.push_back(elem.get_word());

    return ans;
}

pair<string, vector<string>> database::get_multiple(const string &question) const
{
    auto meaning = search_meaning(question);
    vector<string> ans;

    random_device rd;
    vector<const entity *> aux;
    mt19937 mt(rd());

    if (data.size() < NO_CHOICES)
    {
        for_each(data.cbegin(), data.cend(), [&ans](entity elem)
                 { ans.push_back(elem.get_meaning()); });
    }
    else
    {
        for (auto &elem : data)
            aux.push_back(&elem);

        ans.push_back(meaning);
        uniform_int_distribution<int> idist(0, aux.size() - 1);

        for (auto i = 1; i < NO_CHOICES; i++)
        {
            auto index = idist(mt);
            auto elem = aux.at(index);
            auto meaning2 = elem->get_meaning();
            auto it = find(ans.begin(), ans.end(), meaning2);
            if (it == ans.end())
                ans.push_back(meaning2);
            else
                i--;
        }
    }

    shuffle(ans.begin(), ans.end(), default_random_engine(rd()));

    return make_pair(meaning, ans);
}

int database::get_size() const
{
    return data.size();
}