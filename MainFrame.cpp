#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "MainFrame.h"
#include "AddFrame.h"
#include "QuizFrame.h"
#include "constants.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

    wxButton *buttonAdd = new wxButton(panel, wxID_ANY, "Add word", wxPoint(BUTTON_X(BUTTON_WIDTH), 200), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);

    wxButton *buttonSearch = new wxButton(panel, wxID_ANY, "Search word", wxPoint(BUTTON_X(BUTTON_WIDTH), 300), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    wxButton *buttonDelete = new wxButton(panel, wxID_ANY, "Delete word", wxPoint(BUTTON_X(BUTTON_WIDTH), 400), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    wxButton *buttonQuiz = new wxButton(panel, wxID_ANY, "Quiz", wxPoint(BUTTON_X(BUTTON_WIDTH), 500), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonQuiz->Bind(wxEVT_BUTTON, &MainFrame::OnQuiz, this);
}

void MainFrame::OnAdd(wxCommandEvent &evt)
{
    AddFrame *addFrame = new AddFrame();
    addFrame->SetClientSize(WIDTH, HEIGHT);
    addFrame->Center();
    addFrame->Show();
}

void MainFrame::OnQuiz(wxCommandEvent &evt)
{
    QuizFrame *quizFrame = new QuizFrame();
    quizFrame->SetClientSize(WIDTH, HEIGHT);
    quizFrame->Center();
    quizFrame->Show();
}

void MainFrame::OnButtonClicked(wxCommandEvent &evt)
{
    // wxLogStatus("ButtonClicked");
    wxLogMessage("Button clicked!");
}

void MainFrame::OnSliderChanged(wxCommandEvent &evt)
{
    wxString str = wxString::Format("Slider value: %d", evt.GetInt());
    wxLogStatus(str);
}

void MainFrame::OnTextChanged(wxCommandEvent &evt)
{
    wxString str = wxString::Format("Text: %s", evt.GetString());
    wxLogStatus(str);
}

void MainFrame::OnButton1Clicked(wxCommandEvent &evt)
{
    wxLogStatus("Button 1 clicked!");
    evt.Skip();
    wxFrame *nextFrame = new wxFrame(nullptr, wxID_ANY, "Next frame");
    nextFrame->CenterOnParent();
    nextFrame->Show();
}

void MainFrame::OnButton2Clicked(wxCommandEvent &evt)
{
    wxLogStatus("Button 2 clicked!");
    evt.Skip();
}

void MainFrame::OnClose(wxCloseEvent &evt)
{
    wxLogMessage("Frame Closed");
    evt.Skip();
}

void MainFrame::OnMouseEvent(wxMouseEvent &evt)
{
    wxPoint mousePos = wxGetMousePosition();
    wxString message = wxString::Format("Mouse Event: (%d, %d)", mousePos.x, mousePos.y);
    wxLogStatus(message);
}

void MainFrame::OnKeyEvent(wxKeyEvent &evt)
{
    if (evt.GetUnicodeKey() == 'A')
    {
        wxLogStatus("A was pressed");
        return;
    }

    if (evt.GetKeyCode() == WXK_HOME)
    {
        wxLogStatus("Home was pressed");
        return;
    }

    wxChar keyChar = evt.GetUnicodeKey();
    if (keyChar == WXK_NONE)
    {
        int keyCode = evt.GetKeyCode();
        wxLogStatus("Key Event %d", keyCode);
    }
    else
    {
        wxLogStatus("Key Event: %c", keyChar);
    }
}