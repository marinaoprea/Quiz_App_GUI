#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "SearchFrame.h"
#include "constants.h"
#include "exceptions.h"

SearchFrame::SearchFrame() : wxFrame(nullptr, wxID_ANY, "Search")
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:", wxPoint(200, 200), wxSize(200, -1));

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxPoint(300, 200), wxSize(500, -1), wxTE_PROCESS_ENTER);

    search = new wxButton(panel, wxID_ANY, "Search", wxPoint(BUTTON_X(100), 450), wxSize(100, 50));

    search->Bind(wxEVT_BUTTON, &SearchFrame::OnSearch, this);
    ctrlWord->Bind(wxEVT_TEXT_ENTER, &SearchFrame::OnEnter, this);

    wxStatusBar *statusBar = CreateStatusBar();
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
