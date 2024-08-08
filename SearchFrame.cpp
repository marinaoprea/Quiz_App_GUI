#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "SearchFrame.h"
#include "constants.h"
#include "exceptions.h"

SearchFrame::SearchFrame() : wxFrame(nullptr, wxID_ANY, "Search")
{
    this->SetFont(this->GetFont().Scale(1.5));

    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:");

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxDefaultPosition, wxSize(-1, 50), wxTE_PROCESS_ENTER);

    search = new wxButton(panel, wxID_ANY, "Search", wxDefaultPosition, wxSize(150, 75));

    search->Bind(wxEVT_BUTTON, &SearchFrame::OnSearch, this);
    ctrlWord->Bind(wxEVT_TEXT_ENTER, &SearchFrame::OnEnter, this);

    wxStatusBar *statusBar = CreateStatusBar();

    Scale();
}

void SearchFrame::Scale()
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    sizer->AddStretchSpacer();

    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);
    textSizer->Add(textWord, wxSizerFlags().Center());
    textSizer->AddSpacer(10);
    textSizer->Add(ctrlWord, wxSizerFlags().Proportion(1));

    sizer->Add(textSizer, wxSizerFlags().Center().Expand().Border(wxLEFT | wxRIGHT, 50));

    wxBoxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags2 = wxSizerFlags().Center();
    buttonsSizer->Add(search, flags2);

    sizer->AddSpacer(75);
    sizer->Add(buttonsSizer, wxSizerFlags().Center());

    sizer->AddStretchSpacer();

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void SearchFrame::OnSearch(wxCommandEvent &evt)
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
        string meaning = db->search_meaning(word);
        wxLogMessage(wxString(word + " = " + meaning));
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

void SearchFrame::OnEnter(wxCommandEvent &evt)
{
    OnSearch(evt);
}
