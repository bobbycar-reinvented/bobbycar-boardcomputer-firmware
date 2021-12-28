#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class TaskmanagerMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_TASKMANAGER>
{
public:
    TaskmanagerMenu();
    void back() override;
};
