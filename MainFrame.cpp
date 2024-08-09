#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "MainFrame.h"
#include "AddFrame.h"
#include "QuizFrame.h"
#include "DeleteFrame.h"
#include "SearchFrame.h"
#include "MultFrame.h"
#include "constants.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->SetFont(this->GetFont().Scale(TEXT_SCALE));

    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

    buttonAdd = new wxButton(panel, wxID_ANY, "Add word", wxDefaultPosition, wxSize(MAIN_BUTTON_W, MAIN_BUTTON_H));
    buttonAdd->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);

    buttonSearch = new wxButton(panel, wxID_ANY, "Search word", wxDefaultPosition, wxSize(MAIN_BUTTON_W, MAIN_BUTTON_H));
    buttonSearch->Bind(wxEVT_BUTTON, &MainFrame::OnSearch, this);

    buttonDelete = new wxButton(panel, wxID_ANY, "Delete word", wxDefaultPosition, wxSize(MAIN_BUTTON_W, MAIN_BUTTON_H));
    buttonDelete->Bind(wxEVT_BUTTON, &MainFrame::OnDelete, this);

    buttonQuiz = new wxButton(panel, wxID_ANY, "Quiz", wxDefaultPosition, wxSize(MAIN_BUTTON_W, MAIN_BUTTON_H));
    buttonQuiz->Bind(wxEVT_BUTTON, &MainFrame::OnQuiz, this);

    buttonMultiple = new wxButton(panel, wxID_ANY, "Mult Choice", wxDefaultPosition, wxSize(MAIN_BUTTON_W, MAIN_BUTTON_H));
    buttonMultiple->Bind(wxEVT_BUTTON, &MainFrame::OnMult, this); 

    Scale();
}

void MainFrame::Scale()
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flags = wxSizerFlags().Center();
    mainSizer->AddStretchSpacer(1);
    mainSizer->Add(buttonAdd, flags);
    mainSizer->AddSpacer(MAIN_SPACER);
    mainSizer->Add(buttonSearch, flags);
    mainSizer->AddSpacer(MAIN_SPACER);
    mainSizer->Add(buttonDelete, flags);
    mainSizer->AddSpacer(MAIN_SPACER);
    mainSizer->Add(buttonQuiz, flags);
    mainSizer->AddSpacer(MAIN_SPACER);
    mainSizer->Add(buttonMultiple, flags);
    mainSizer->AddStretchSpacer(1);

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
}

void MainFrame::OnMult(wxCommandEvent &evt)
{
    MultFrame *multFrame = new MultFrame();
    multFrame->SetClientSize(WIDTH, HEIGHT);
    multFrame->Center();
    multFrame->Show();
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