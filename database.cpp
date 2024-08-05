#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "nlohmann/json.hpp"
#include "helper.h"
#include "database.h"
#include "entity.h"
#include "cmath"

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

    modify_check();
}

// first = modified, second = correct
pair<bool, bool> database::quest(vector<const entity *> &v, int nr)
{
    auto elem = v.at(nr);
    std::cout << "What does " + elem->get_word() + " mean?\n";
    string meaning;
    std::getline(std::cin, meaning);

    if (meaning != elem->get_meaning())
    {
        std::cout << "Wrong! " + elem->get_word() + " = " + elem->get_meaning() + "\n";
        return {false, false};
    }

    std::cout << "Correct!\n";

    if (elem->get_lives() == 1)
    {
        std::cout << "Do you want to keep word " + elem->get_word() + " for further usage? Yes/No\n";

        string ans;
        std::getline(std::cin, ans);

        if (equal_strings(ans, "Yes"))
        {
            return {false, true};
        }
        else
        {
            std::cout << "Word " + elem->get_word() + " was deleted.\n";
            data.erase(*elem);
            v.erase(v.begin() + nr);
            return {true, true};
        }
    }

    auto elem_set = data.find(*elem);
    elem_set->decrement_lives();
    return {false, true};
}

void database::run_quiz()
{
    vector<const entity *> aux;
    random_device rd;
    mt19937 mt(rd());

    for (auto &elem : data)
    {
        aux.push_back(&elem);
    }

    uniform_int_distribution<int> idist(0, aux.size() - 1);

    std::cin.get();

    bool modified{false};
    short int counter{0};
    for (int i = 0; i < NO_QUESTIONS; i++)
    {
        if (data.empty())
        {
            std::cout << "Congratulations! No more words to learn!\n";
            return;
        }

        auto nr = idist(mt);
        auto ans = quest(aux, nr);
        if (ans.first)
            idist = uniform_int_distribution<int>(0, aux.size() - 1);
        if (ans.second)
            counter++;
    }

    std::cout << "Quiz results: " << counter << " / " << NO_QUESTIONS << '\n';
}

void database::modify_check()
{
    last_save++;
    if (last_save == AUTOSAVE_LIMIT)
    {
        dump_to_file(DATABASE_PATH);
        std::cout << "Autosave performed!\n";
        last_save = 0;
    }
}

vector<string> database::get_quiz_questions() const
{
    vector<const entity *> aux;
    vector<string> ans;
    random_device rd;
    mt19937 mt(rd());

    for (auto &elem : data)
    {
        aux.push_back(&elem);
    }

    uniform_int_distribution<int> idist(0, aux.size() - 1);

    for (auto i = 0; i < NO_QUESTIONS; i++)
    {
        auto index = idist(mt);
        auto elem = aux.at(index);
        ans.push_back(elem->get_word());
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