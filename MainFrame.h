#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);
private:
    const short int BUTTON_WIDTH = 100;
    const short int BUTTON_HEIGHT = 50;

    wxPanel *panel;
    wxButton *buttonAdd;
    wxButton *buttonSearch;
    wxButton *buttonDelete;
    wxButton *buttonQuiz;

    void Scale();

    void OnAdd(wxCommandEvent &evt);
    void OnQuiz(wxCommandEvent &evt);
    void OnDelete(wxCommandEvent &evt);
    void OnSearch(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
};