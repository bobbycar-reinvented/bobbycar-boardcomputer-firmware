#include "networksettingsmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <fmt/format.h>
#include <icons/back.h>
#include <menuitem.h>
#include <screenmanager.h>

// local includes
#include "displays/qrdisplay.h"
#include "globals.h"
#include "settingsmenu.h"
#include "texthelpers/networktexthelpers.h"
#include "wifiapsettingsmenu.h"
#include "wifistasettingsmenu.h"

using namespace espgui;

namespace {
constexpr char TEXT_STASETTINGS[] = "STA Settings";
constexpr char TEXT_APSETTINGS[] = "AP Settings";
constexpr char TEXT_APQRCODE[] = "AP QR Code";
constexpr char TEXT_BACK[] = "Back";
} // namespace

NetworkSettingsMenu::NetworkSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_STASETTINGS>, SwitchScreenAction<WifiStaSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_APSETTINGS>,  SwitchScreenAction<WifiApSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_APQRCODE>,    NetworkAccessPointQRAction>>();

    constructMenuItem<makeComponent<MenuItem,     WifiDefaultMacText,           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem,     WifiBaseMacText,              DummyAction>>();
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{0});
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{1});
    constructMenuItem<makeComponentArgs<MenuItem, DnsText,                      DummyAction>>(uint8_t{2});
    constructMenuItem<makeComponent<MenuItem,     WifiTxPowerText,              DummyAction>>();
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

void NetworkAccessPointQRAction::triggered()
{
    std::string qr = fmt::format("WIFI:T:WPA;S:{};P:{};H:;", configs.wifiApName.value, configs.wifiApKey.value);
    espgui::switchScreen<QrDisplay<NetworkSettingsMenu>>(qr);
}
