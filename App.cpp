#include <wx/wx.h>
#include "App.h"
#include "MainFrame.h"
#include "constants.h"
#include "database.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    db->load();

    MainFrame *mainFrame = new MainFrame("Summer 2024");
    mainFrame->SetClientSize(WIDTH, HEIGHT);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}