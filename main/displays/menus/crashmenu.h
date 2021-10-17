#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include <esp_log.h>


// forward declares
namespace {
class SettingsMenu;

class AssertAction : public virtual ActionInterface { public: void triggered() override { assert(0); } };
class DivideByZeroAction : public virtual ActionInterface { public: void triggered() override { int goodbye = 42 / 0; ESP_LOGW("divByZero", "%i", goodbye); } };


} // namespace

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
