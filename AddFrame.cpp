#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "AddFrame.h"
#include "constants.h"

AddFrame::AddFrame() : wxFrame(nullptr, wxID_ANY, "Add")
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:", wxPoint(200, 200), wxSize(200, -1));
    textMeaning = new wxStaticText(panel, wxID_ANY, "Meaning:", wxPoint(200, 300), wxSize(200, -1));

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxPoint(300, 200), wxSize(500, -1));
    ctrlMeaning = new wxTextCtrl(panel, wxID_ANY, "Insert meaning", wxPoint(300, 300), wxSize(500, -1));

    add = new wxButton(panel, wxID_ANY, "Add", wxPoint(BUTTON_X(100), 450), wxSize(100, 50));
    save = new wxButton(panel, wxID_ANY, "Save", wxPoint(BUTTON_X(100), 550), wxSize(100, 50));

    add->Bind(wxEVT_BUTTON, &AddFrame::OnAdd, this);
    save->Bind(wxEVT_BUTTON, &AddFrame::OnSave, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &AddFrame::OnClose, this);

    wxStatusBar *statusBar = CreateStatusBar();
}

void AddFrame::OnAdd(wxCommandEvent &evt)
{
    std::string word = ctrlWord->GetLineText(0).ToStdString();
    std::string meaning = ctrlMeaning->GetLineText(0).ToStdString();

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
    wxLogStatus(this, wxString(ans));

}

void AddFrame::OnSave(wxCommandEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
    wxLogStatus(this, "Saved!");
}

void AddFrame::OnClose(wxCloseEvent &evt)
{
    db->dump_to_file(DATABASE_PATH);
    evt.Skip();
}