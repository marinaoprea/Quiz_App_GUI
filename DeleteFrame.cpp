#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include "DeleteFrame.h"
#include "constants.h"
#include "exceptions.h"

DeleteFrame::DeleteFrame() : wxFrame(nullptr, wxID_ANY, "Delete")
{
    panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    textWord = new wxStaticText(panel, wxID_ANY, "Word:", wxPoint(200, 200), wxSize(200, -1));

    ctrlWord = new wxTextCtrl(panel, wxID_ANY, "Insert word", wxPoint(300, 200), wxSize(500, -1), wxTE_PROCESS_ENTER);

    deletebt = new wxButton(panel, wxID_ANY, "Delete", wxPoint(BUTTON_X(100), 450), wxSize(100, 50));
    save = new wxButton(panel, wxID_ANY, "Save", wxPoint(BUTTON_X(100), 550), wxSize(100, 50));

    deletebt->Bind(wxEVT_BUTTON, &DeleteFrame::OnDelete, this);
    save->Bind(wxEVT_BUTTON, &DeleteFrame::OnSave, this);
    ctrlWord->Bind(wxEVT_TEXT_ENTER, &DeleteFrame::OnEnter, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &DeleteFrame::OnClose, this);

    wxStatusBar *statusBar = CreateStatusBar();
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
    catch (std::exception &exc)
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