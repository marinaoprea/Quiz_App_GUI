#include <wx/wx.h>
#include "QuizFrame.h"
#include <iostream>

QuizFrame::QuizFrame() : wxFrame(nullptr, wxID_ANY, "Quiz")
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    text = new wxStaticText(panel, wxID_ANY, "", wxPoint(200, 300), wxSize(500, -1));
    textCtrl = new wxTextCtrl(panel, wxID_ANY, "Insert meaning", wxPoint(200, 400), wxSize(500, -1));
    check = new wxButton(panel, wxID_ANY, "Check", wxPoint(BUTTON_X(100), 500), wxSize(100, 50));

    check->Bind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &QuizFrame::OnClose, this);

    try
    {
        questions = db->get_quiz_questions();
        RunQuiz();
    }
    catch(std::exception &exc) 
    {
        check->Unbind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
        wxLogMessage(exc.what());
    }
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
    if (correct)
    {
        auto rc = db->decrement_lives(word);
        wxLogMessage("Correct");
        good++;
        no_questions--;

        if (rc)
        {
            wxMessageDialog dialog(this, "Do you want to erase word " + word + " ?", "Erase", wxYES_NO);
            auto result = dialog.ShowModal();
            if (result == wxID_YES)
                db->erase_word(word);
        }

        RunQuiz();
        return;
    }

    wxLogMessage("Wrong");
    no_questions--;
    RunQuiz();
}

void QuizFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}
