#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);
private:
    const short int BUTTON_WIDTH = 100;
    const short int BUTTON_HEIGHT = 50;

    void OnAdd(wxCommandEvent &evt);
    void OnQuiz(wxCommandEvent &evt);

    void OnButtonClicked(wxCommandEvent &evt);
    void OnSliderChanged(wxCommandEvent &evt);
    void OnTextChanged(wxCommandEvent &evt);
    void OnButton1Clicked(wxCommandEvent &evt);
    void OnButton2Clicked(wxCommandEvent &evt);
    void OnClose(wxCloseEvent &evt);
    void OnMouseEvent(wxMouseEvent &evt);
    void OnKeyEvent(wxKeyEvent &evt);
};