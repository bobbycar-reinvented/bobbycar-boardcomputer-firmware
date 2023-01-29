#include "invertmenu.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "actions/popscreenaction.h"
#include "guihelpers/bobbycheckbox.h"

namespace bobby {

namespace {
constexpr char TEXT_SETINVERTED[] = "Set inverted";
constexpr char TEXT_INVERTFRONTLEFT[] = "Invert front left";
constexpr char TEXT_INVERTFRONTRIGHT[] = "Invert front right";
constexpr char TEXT_INVERTBACKLEFT[] = "Invert back left";
constexpr char TEXT_INVERTBACKRIGHT[] = "Invert back right";
} // namespace

InvertMenu::InvertMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  BobbyCheckbox, FrontLeftInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, BobbyCheckbox, FrontRightInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   BobbyCheckbox, BackLeftInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  BobbyCheckbox, BackRightInvertedAccessor>>();
}

std::string InvertMenu::title() const
{
    return TEXT_SETINVERTED;
}

void InvertMenu::back()
{
    espgui::popScreen();
}

} // namespace bobby
