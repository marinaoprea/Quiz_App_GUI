#pragma once

#include <wx/wx.h>
#include "database.h"

extern database *db;

class SearchFrame : public wxFrame
{
public:
    SearchFrame();

private:
    wxPanel *panel;
    wxStaticText *textWord;
    wxTextCtrl *ctrlWord;
    wxButton *search;

    void OnSearch(wxCommandEvent &evt);
    void OnEnter(wxCommandEvent &evt);
};