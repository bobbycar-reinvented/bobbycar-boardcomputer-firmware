#include "taskmanagermenu.h"

// 3rdparty lib includes
#include <icons/back.h>
#include <actions/switchscreenaction.h>
#include <actions/dummyaction.h>
#include <schedulertask.h>

// local includes
#include "displays/menus/debugmenu.h"
#include "taskmanager.h"

using namespace espgui;

TaskmanagerMenu::TaskmanagerMenu()
{
    for (const auto &task : schedulerTasks)
        constructMenuItem<makeComponentArgs<MenuItem, ChangeableText, DummyAction>>(std::string{task.name()});
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void TaskmanagerMenu::back()
{
    switchScreen<DebugMenu>();
}
