#pragma once

constexpr short int HEIGHT = 800;
constexpr short int WIDTH = 1000;

#define BUTTON_X(X) ((WIDTH - X) / 2)

constexpr short int AUTOSAVE_LIMIT = 3;
constexpr short int INITIAL_WORD_LIVES = 3;
constexpr short int NO_QUESTIONS = 5;
const std::string DATABASE_PATH{"database.txt"};
const std::string WORD{"word"};
const std::string MEANING{"meaning"};
const std::string LIVES{"lives"};
