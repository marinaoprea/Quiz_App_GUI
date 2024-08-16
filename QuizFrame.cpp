#include <wx/wx.h>
#include <chrono>
#include <iostream>
#include "QuizFrame.h"
#include "exceptions.h"

QuizFrame::QuizFrame() : wxFrame(nullptr, wxID_ANY, "Quiz")
{
    this->SetFont(this->GetFont().Scale(TEXT_SCALE));
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    text = new wxStaticText(panel, wxID_ANY, "");
    textCtrl = new wxTextCtrl(panel, wxID_ANY, "Insert meaning", wxDefaultPosition, wxSize(-1, CTRL_HEIGHT), wxTE_PROCESS_ENTER);
    check = new wxButton(panel, wxID_ANY, "Check", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));

    check->Bind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
    textCtrl->Bind(wxEVT_TEXT_ENTER, &QuizFrame::OnEnter, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &QuizFrame::OnClose, this);

    CreateStatusBar();
    Scale();

    time = chrono::steady_clock::now();

    try
    {
        questions = db->get_quiz_questions();
        RunQuiz();
    }
    catch (std::exception &exc)
    {
        check->Unbind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
        wxLogMessage(exc.what());
        this->Close();
    }
}

void QuizFrame::Scale() noexcept
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddStretchSpacer();

    sizer->Add(text, wxSizerFlags().Center());
    sizer->AddSpacer(50);
    sizer->Add(textCtrl, wxSizerFlags().Expand().Border(wxLEFT | wxRIGHT, CTRL_BORDER));

    wxBoxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags2 = wxSizerFlags().Center();
    buttonsSizer->Add(check, flags2);

    sizer->AddSpacer(75);
    sizer->Add(buttonsSizer, wxSizerFlags().Center());

    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void QuizFrame::RunQuiz()
{
    if (no_questions == 0)
    {
        auto time2 = chrono::steady_clock::now();

        auto diff = chrono::duration_cast<chrono::seconds>(time2 - time).count();
        auto minutes = diff / 60;
        auto sec = diff - minutes * 60;
        text->SetLabelText(wxString::Format("Results: %d / %d\nTime taken: %lld : %lld", good, NO_QUESTIONS, minutes, sec));
        check->Unbind(wxEVT_BUTTON, &QuizFrame::OnCheck, this);
        textCtrl->Unbind(wxEVT_TEXT_ENTER, &QuizFrame::OnEnter, this);
        textCtrl->Clear();
        return;
    }

    std::string str = questions.at(no_questions - 1);
    text->SetLabelText(wxString::Format("What does %s mean?", str));
    text->SetFont(text->GetFont().Bold());
}

void QuizFrame::OnCheck(wxCommandEvent &evt)
{
    std::string word = questions.at(no_questions - 1);
    std::string meaning = textCtrl->GetLineText(0).ToStdString();

    textCtrl->Clear();

    if (meaning.empty())
    {
        wxLogMessage("Meaning field empty");
        return;
    }

    int correct = db->check(word, meaning);
    if (!correct)
    {
        auto rc = db->decrement_lives(word);
        wxLogStatus(this, "Correct");
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

    if (correct <= ACC_DIFF) 
    {
        wxLogMessage(wxString::Format("Wrong by %d differences! Try again!", correct));
        return;
    }

    try
    {
        string meaning = db->search_meaning(word);
        wxLogMessage(wxString("Wrong! " + word + " = " + meaning));
    }
    catch (WordNotFound &exc)
    {
        auto p = exc.what();
        wxLogMessage(p);
        delete p;
    }
    no_questions--;
    RunQuiz();
}

void QuizFrame::OnEnter(wxCommandEvent &evt)
{
    OnCheck(evt);
}

void QuizFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}
