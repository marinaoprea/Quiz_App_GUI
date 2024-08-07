#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "MainFrame.h"
#include "AddFrame.h"
#include "QuizFrame.h"
#include "DeleteFrame.h"
#include "SearchFrame.h"
#include "constants.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

    wxButton *buttonAdd = new wxButton(panel, wxID_ANY, "Add word", wxPoint(BUTTON_X(BUTTON_WIDTH), 200), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);

    wxButton *buttonSearch = new wxButton(panel, wxID_ANY, "Search word", wxPoint(BUTTON_X(BUTTON_WIDTH), 300), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonSearch->Bind(wxEVT_BUTTON, &MainFrame::OnSearch, this);

    wxButton *buttonDelete = new wxButton(panel, wxID_ANY, "Delete word", wxPoint(BUTTON_X(BUTTON_WIDTH), 400), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonDelete->Bind(wxEVT_BUTTON, &MainFrame::OnDelete, this);

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

void MainFrame::OnClose(wxCloseEvent &evt)
{
    wxLogMessage("Frame Closed");
    evt.Skip();
}

void MainFrame::OnDelete(wxCommandEvent &evt)
{
    DeleteFrame *deleteFrame = new DeleteFrame();
    deleteFrame->SetClientSize(WIDTH, HEIGHT);
    deleteFrame->Center();
    deleteFrame->Show();
}

void MainFrame::OnSearch(wxCommandEvent &evt)
{
    SearchFrame *searchFrame = new SearchFrame();
    searchFrame->SetClientSize(WIDTH, HEIGHT);
    searchFrame->Center();
    searchFrame->Show();
}