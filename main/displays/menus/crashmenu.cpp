#include "crashmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "actions/assertaction.h"
#include "actions/dividebyzeroaction.h"
#include "displays/menus/settingsmenu.h"

namespace {
constexpr char TEXT_CRASHMENU[] = "Crash Menu";
constexpr char TEXT_CRASH_ASSERT[] = "assert(0)";
constexpr char TEXT_CRASH_DIVZERO[] = "42 / 0";
constexpr char TEXT_BACK[] = "Back";
} // namespace

CrashMenu::CrashMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_ASSERT>,    AssertAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_DIVZERO>,   DivideByZeroAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string CrashMenu::text() const
{
    return TEXT_CRASHMENU;
}

void CrashMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
