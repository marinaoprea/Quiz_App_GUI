#pragma once
#include <wx/wx.h>
#include "database.h"

database *db = new database();

class App : public wxApp
{
public:
    bool OnInit();
};