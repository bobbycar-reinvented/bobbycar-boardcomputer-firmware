#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/assertaction.h"
#include "actions/dividebyzeroaction.h"
#include "icons/back.h"
#include "texts.h"

using namespace espgui;

namespace {

class CrashMenu :
    public MenuDisplay,
    public StaticText<TEXT_CRASHMENU>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    CrashMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_ASSERT>,    AssertAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_DIVZERO>,   DivideByZeroAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
