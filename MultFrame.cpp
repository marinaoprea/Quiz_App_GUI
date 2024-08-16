#include <wx/wx.h>
#include <chrono>
#include "MultFrame.h"
#include "exceptions.h"
#include <iostream>

MultFrame::MultFrame() : wxFrame(nullptr, wxID_ANY, "Multiple choice")
{
    this->SetFont(this->GetFont().Scale(TEXT_SCALE));
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    text = new wxStaticText(panel, wxID_ANY, "");
    wxArrayString arr;
    for (int i = 0; i < NO_CHOICES; i++)
        arr.push_back("");
    choice = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(-1, CTRL_HEIGHT), arr);

    check = new wxButton(panel, wxID_ANY, "Check", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));

    check->Bind(wxEVT_BUTTON, &MultFrame::OnCheck, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MultFrame::OnClose, this);

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
        check->Unbind(wxEVT_BUTTON, &MultFrame::OnCheck, this);
        wxLogMessage(exc.what());
        this->Close();
    }
}

void MultFrame::Scale() noexcept
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddStretchSpacer();

    sizer->Add(text, wxSizerFlags().Center());
    sizer->AddSpacer(50);
    sizer->Add(choice, wxSizerFlags().Expand().Border(wxLEFT | wxRIGHT, CTRL_BORDER));

    wxBoxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags2 = wxSizerFlags().Center();
    buttonsSizer->Add(check, flags2);

    sizer->AddSpacer(75);
    sizer->Add(buttonsSizer, wxSizerFlags().Center());

    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void MultFrame::RunQuiz()
{
    if (no_questions == 0)
    {
        auto time2 = chrono::steady_clock::now();

        auto diff = chrono::duration_cast<chrono::seconds>(time2 - time).count();
        auto minutes = diff / 60;
        auto sec = diff - minutes * 60;
        text->SetLabelText(wxString::Format("Results: %d / %d\nTime taken: %lld : %lld", good, NO_QUESTIONS, minutes, sec));
        check->Unbind(wxEVT_BUTTON, &MultFrame::OnCheck, this);
        return;
    }

    std::string str = questions.at(no_questions - 1);
    text->SetLabelText(wxString::Format("What does %s mean?", str));
    text->SetFont(text->GetFont().Bold());

    auto p = db->get_multiple(str);
    correct = p.first;

    for (int i = 0; i < NO_CHOICES; i++)
        choice->SetString(i, "-");

    auto minim = std::min(static_cast<int>(NO_CHOICES), db->get_size());
    for (int i = 0; i < minim; i++)
        choice->SetString(i, wxString(p.second.at(i)));
    choice->Select(0);
}

void MultFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}

void MultFrame::OnCheck(wxCommandEvent &evt)
{
    auto word = questions.at(no_questions - 1);
    auto ans = choice->GetString(choice->GetSelection());
    auto str = wxString(this->correct);
    bool is_correct = (str == ans);
    if (is_correct)
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

    wxLogMessage(wxString("Wrong! " + word + " = " + this->correct));
    no_questions--;
    RunQuiz();
}