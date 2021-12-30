#include "enablemenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/menus/controllerhardwaresettingsmenu.h"
#include "accessors/settingsaccessors.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_ENABLEFRONTLEFT[] = "Enable front left";
constexpr char TEXT_ENABLEFRONTRIGHT[] = "Enable front right";
constexpr char TEXT_ENABLEBACKLEFT[] = "Enable back left";
constexpr char TEXT_ENABLEBACKRIGHT[] = "Enable back right";
constexpr char TEXT_BACK[] = "Back";
} // namespace

EnableMenu::EnableMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  BobbyCheckbox, FrontLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, BobbyCheckbox, FrontRightEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   BobbyCheckbox, BackLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  BobbyCheckbox, BackRightEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string EnableMenu::text() const
{
    return TEXT_SETENABLED;
}

void EnableMenu::back()
{
    espgui::switchScreen<ControllerHardwareSettingsMenu>();
}
