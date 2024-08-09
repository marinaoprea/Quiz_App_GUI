#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "AddFrame.h"
#include "constants.h"

AddFrame::AddFrame() : wxFrame(nullptr, wxID_ANY, "Add")
{
    this->SetFont(this->GetFont().Scale(TEXT_SCALE));

    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:");
    textMeaning = new wxStaticText(panel, wxID_ANY, "Meaning:");

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxDefaultPosition, wxSize(-1, CTRL_HEIGHT), wxTE_PROCESS_ENTER);
    ctrlMeaning = new wxTextCtrl(panel, wxID_ANY, "Insert meaning", wxDefaultPosition, wxSize(-1, CTRL_HEIGHT), wxTE_PROCESS_ENTER);

    add = new wxButton(panel, wxID_ANY, "Add", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));
    save = new wxButton(panel, wxID_ANY, "Save", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));

    add->Bind(wxEVT_BUTTON, &AddFrame::OnAdd, this);
    save->Bind(wxEVT_BUTTON, &AddFrame::OnSave, this);
    ctrlMeaning->Bind(wxEVT_TEXT_ENTER, &AddFrame::OnEnterMeaning, this);
    ctrlWord->Bind(wxEVT_TEXT_ENTER, &AddFrame::OnEnterWord, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &AddFrame::OnClose, this);

    wxStatusBar *statusBar = CreateStatusBar();

    Scale();
}

void AddFrame::Scale()
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddStretchSpacer();

    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);
    textSizer->Add(textWord, wxSizerFlags().Center());
    textSizer->AddSpacer(10);
    textSizer->Add(ctrlWord, wxSizerFlags().Proportion(1));

    sizer->Add(textSizer, wxSizerFlags().Center().Expand().Border(wxLEFT | wxRIGHT, CTRL_BORDER));

    wxBoxSizer *meaningSizer = new wxBoxSizer(wxHORIZONTAL);
    meaningSizer->Add(textMeaning, wxSizerFlags().Center());
    meaningSizer->AddSpacer(10);
    meaningSizer->Add(ctrlMeaning, wxSizerFlags().Proportion(1));

    sizer->AddSpacer(10);
    sizer->Add(meaningSizer, wxSizerFlags().Center().Expand().Border(wxLEFT | wxRIGHT, CTRL_BORDER));

    wxBoxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags2 = wxSizerFlags().Center();
    buttonsSizer->Add(add, flags2);
    buttonsSizer->AddSpacer(10);
    buttonsSizer->Add(save, flags2);

    sizer->AddSpacer(25);
    sizer->Add(buttonsSizer, wxSizerFlags().Center());

    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void AddFrame::OnAdd(wxCommandEvent &evt)
{
    std::string word = ctrlWord->GetLineText(0).ToStdString();
    std::string meaning = ctrlMeaning->GetLineText(0).ToStdString();

    ctrlWord->Clear();
    ctrlMeaning->Clear();

    if (word.empty())
    {
        wxLogMessage("Word field empty");
        return;
    }

    if (meaning.empty())
    {
        wxLogMessage("Meaning field empty");
        return;
    }

    string ans = db->add_word(word, meaning);
    evt.Skip();

    ctrlWord->SetFocus();

    if (ans.find("already exists") != ans.npos)
    {
        wxMessageDialog dialog(this, ans + " Do you want to overwrite it?", "Overwrite", wxYES_NO);
        auto result = dialog.ShowModal();
        if (result == wxID_YES)
        {
            db->erase_word(word);
            db->add_word(word, meaning);
        }
        ctrlWord->SetFocus();
        return;
    }
    wxLogStatus(this, wxString(ans));
}

void AddFrame::OnSave(wxCommandEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
    wxLogStatus(this, "Saved!");
}

void AddFrame::OnEnterMeaning(wxCommandEvent &evt)
{
    OnAdd(evt);
}

void AddFrame::OnEnterWord(wxCommandEvent &evt)
{
    ctrlMeaning->SetFocus();
}

void AddFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}