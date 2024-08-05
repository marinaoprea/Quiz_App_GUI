#pragma once

#include <wx/wx.h>
#include "database.h"

extern database *db;

class AddFrame : public wxFrame
{
public:
    AddFrame();

private:
    wxPanel *panel;
    wxStaticText *textWord;
    wxStaticText *textMeaning;
    wxTextCtrl *ctrlWord;
    wxTextCtrl *ctrlMeaning;
    wxButton *add;
    wxButton *save;

    void OnAdd(wxCommandEvent &evt);
    void OnSave(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
    void OnEnterMeaning(wxCommandEvent &evt);
    void OnEnterWord(wxCommandEvent &evt);
};