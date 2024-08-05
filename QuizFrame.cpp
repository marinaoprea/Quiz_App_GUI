#include <wx/wx.h>
#include "QuizFrame.h"

QuizFrame::QuizFrame() : wxFrame(nullptr, wxID_ANY, "Quiz")
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    text = new wxStaticText(panel, wxID_ANY, "", wxPoint(200, 300), wxSize(500, -1));
    textCtrl = new wxTextCtrl(panel, wxID_ANY, "Insert meaning", wxPoint(200, 400), wxSize(500, -1));
    check = new wxButton(panel, wxID_ANY, "Check", wxPoint(BUTTON_X(100), 500), wxSize(100, 50));

    check->Bind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
    questions = db->get_quiz_questions();
    RunQuiz();
}

void QuizFrame::RunQuiz()
{
    if (no_questions == 0)
    {
        text->SetLabelText(wxString::Format("Results: %d / %d", good, NO_QUESTIONS));
        check->Unbind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
        textCtrl->Clear();
        return;
    }

    std::string str = questions.at(no_questions - 1);
    text->SetLabelText(wxString::Format("What does %s mean?", str));
}

void QuizFrame::OnCheck(wxCommandEvent &evt)
{
    std::string word = questions.at(no_questions - 1);
    std::string meaning = textCtrl->GetLineText(0).ToStdString();

    bool correct = db->check(word, meaning);
    if (correct) {
       // db->decrement_lives(word);
        wxLogMessage("Correct");
        good++;
        no_questions--;
        RunQuiz();
        return;
    }

    wxLogMessage("Wrong");
    no_questions--;
    RunQuiz();
}
