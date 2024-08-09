#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "DeleteFrame.h"
#include "constants.h"
#include "exceptions.h"

DeleteFrame::DeleteFrame() : wxFrame(nullptr, wxID_ANY, "Delete")
{
    this->SetFont(this->GetFont().Scale(TEXT_SCALE));

    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:");

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxDefaultPosition, wxSize(-1, CTRL_HEIGHT), wxTE_PROCESS_ENTER);

    deletebt = new wxButton(panel, wxID_ANY, "Delete", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));
    save = new wxButton(panel, wxID_ANY, "Save", wxDefaultPosition, wxSize(BUTTON_W, BUTTON_H));

    deletebt->Bind(wxEVT_BUTTON, &DeleteFrame::OnDelete, this);
    save->Bind(wxEVT_BUTTON, &DeleteFrame::OnSave, this);
    ctrlWord->Bind(wxEVT_TEXT_ENTER, &DeleteFrame::OnEnter, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &DeleteFrame::OnClose, this);

    wxStatusBar *statusBar = CreateStatusBar();

    Scale();
}

void DeleteFrame::Scale() noexcept
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddStretchSpacer();

    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);
    textSizer->Add(textWord, wxSizerFlags().Center());
    textSizer->AddSpacer(10);
    textSizer->Add(ctrlWord, wxSizerFlags().Proportion(1));

    sizer->Add(textSizer, wxSizerFlags().Center().Expand().Border(wxLEFT | wxRIGHT, CTRL_BORDER));

    wxBoxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags2 = wxSizerFlags().Center();
    buttonsSizer->Add(deletebt, flags2);
    buttonsSizer->AddSpacer(10);
    buttonsSizer->Add(save, flags2);

    sizer->AddSpacer(75);
    sizer->Add(buttonsSizer, wxSizerFlags().Center());

    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void DeleteFrame::OnDelete(wxCommandEvent &evt)
{
    std::string word = ctrlWord->GetLineText(0).ToStdString();

    ctrlWord->Clear();

    if (word.empty())
    {
        wxLogMessage("Word field empty");
        return;
    }

    try
    {
        db->erase_word(word);
        wxLogStatus(this, wxString(word + " was erased"));
    }
    catch (WordNotFound &exc)
    {
        auto p = exc.what();
        wxLogMessage(p);
        delete p;
    }
    evt.Skip();

    ctrlWord->SetFocus();
}

void DeleteFrame::OnSave(wxCommandEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
    wxLogStatus(this, "Saved!");
}

void DeleteFrame::OnEnter(wxCommandEvent &evt)
{
    OnDelete(evt);
}

void DeleteFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}