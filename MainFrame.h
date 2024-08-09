#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);
private:
    wxPanel *panel;
    wxButton *buttonAdd;
    wxButton *buttonSearch;
    wxButton *buttonDelete;
    wxButton *buttonQuiz;
    wxButton *buttonMultiple;

    void Scale();

    void OnMult(wxCommandEvent &evt);
    void OnAdd(wxCommandEvent &evt);
    void OnQuiz(wxCommandEvent &evt);
    void OnDelete(wxCommandEvent &evt);
    void OnSearch(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
};