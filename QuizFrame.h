#pragma once

#include <wx/wx.h>
#include <vector>
#include <chrono>
#include "constants.h"
#include "database.h"

extern database *db;

class QuizFrame : public wxFrame {
public:
    QuizFrame();

private:
    chrono::steady_clock::time_point time;
    short int no_questions{NO_QUESTIONS};
    short int good{0};
    wxPanel *panel;
    wxButton *check;
    wxStaticText *text;
    wxTextCtrl *textCtrl;

    std::vector<std::string> questions;

    void Scale() noexcept;

    void RunQuiz();
    void OnCheck(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
    void OnEnter(wxCommandEvent &evt);
};