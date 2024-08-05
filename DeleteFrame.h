#pragma once

#include <wx/wx.h>
#include "database.h"

extern database *db;

class DeleteFrame : public wxFrame
{
public:
    DeleteFrame();

private:
    wxPanel *panel;
    wxStaticText *textWord;
    wxTextCtrl *ctrlWord;
    wxButton *deletebt;
    wxButton *save;

    void OnDelete(wxCommandEvent &evt);
    void OnSave(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
    void OnEnter(wxCommandEvent &evt);
};