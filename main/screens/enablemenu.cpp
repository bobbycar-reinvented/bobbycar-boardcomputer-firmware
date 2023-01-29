#include "enablemenu.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "actions/popscreenaction.h"
#include "guihelpers/bobbycheckbox.h"

namespace bobby {

namespace {
constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_ENABLEFRONTLEFT[] = "Enable front left";
constexpr char TEXT_ENABLEFRONTRIGHT[] = "Enable front right";
constexpr char TEXT_ENABLEBACKLEFT[] = "Enable back left";
constexpr char TEXT_ENABLEBACKRIGHT[] = "Enable back right";
} // namespace

EnableMenu::EnableMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  BobbyCheckbox, FrontLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, BobbyCheckbox, FrontRightEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   BobbyCheckbox, BackLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  BobbyCheckbox, BackRightEnabledAccessor>>();
}

std::string EnableMenu::title() const
{
    return TEXT_SETENABLED;
}

void EnableMenu::back()
{
    espgui::popScreen();
}

} // namespace bobby
