#include "blesettingsmenu.h"

// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "bletexthelpers.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

#ifdef FEATURE_BLE
namespace {
constexpr char TEXT_BLESETTINGS[] = "BLE settings";
constexpr char TEXT_BLEENABLED[] = "BLE enabled";
constexpr char TEXT_BACK[] = "Back";
} // namespace

BleSettingsMenu::BleSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLEENABLED>, BobbyCheckbox, BleEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, BleServerPeerDevicesText,    DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BleCharacSubscribedText,     DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string BleSettingsMenu::text() const
{
    return TEXT_BLESETTINGS;
}

void BleSettingsMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
#endif
