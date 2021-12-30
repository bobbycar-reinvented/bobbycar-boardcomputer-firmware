#include "networksettingsmenu.h"

// 3rdparty lib includes
#include <menuitem.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <icons/back.h>
#include <screenmanager.h>
#include <fmt/format.h>

// local includes
#include "wifistasettingsmenu.h"
#include "wifiapsettingsmenu.h"
#include "settingsmenu.h"
#include "texthelpers/networktexthelpers.h"

using namespace espgui;

namespace {
constexpr char TEXT_STASETTINGS[] = "STA Settings";
constexpr char TEXT_APSETTINGS[] = "AP Settings";
constexpr char TEXT_BACK[] = "Back";
} // namespace

NetworkSettingsMenu::NetworkSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_STASETTINGS>, SwitchScreenAction<WifiStaSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_APSETTINGS>,  SwitchScreenAction<WifiApSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem,     WifiDefaultMacText,           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem,     WifiBaseMacText,              DummyAction>>();
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{0});
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{1});
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{2});
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_BACK>,        SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
}

std::string NetworkSettingsMenu::text() const
{
    return "Network settings";
}

void NetworkSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
