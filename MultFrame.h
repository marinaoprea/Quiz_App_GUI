#pragma once

#include <wx/wx.h>
#include <vector>
#include "constants.h"
#include "database.h"

extern database *db;

class MultFrame : public wxFrame {
public:
    MultFrame();

private:
    short int no_questions{NO_QUESTIONS};
    short int good{0};
    wxPanel *panel;
    wxButton *check;
    wxStaticText *text;
    wxChoice *choice;
    string correct;

    std::vector<std::string> questions;

    void Scale() noexcept;
    void OnCheck(wxCommandEvent &evt);
    void RunQuiz();
    void OnClose(wxCloseEvent &evt);
};