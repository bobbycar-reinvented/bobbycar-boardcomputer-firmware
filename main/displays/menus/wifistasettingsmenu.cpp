#include "wifistasettingsmenu.h"

// 3rdparty lib includes
#include <menuitem.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <checkboxicon.h>
#include <actions/toggleboolaction.h>
#include <icons/back.h>
#include <screenmanager.h>

// local includes
#include "wifistascanmenu.h"
#include "wifistaconfigsmenu.h"
#include "accessors/wifistaconfigaccessors.h"
#include "networksettingsmenu.h"
#include "texthelpers/wifistatexthelpers.h"

using namespace espgui;

namespace {
constexpr char TEXT_ENABLED[] = "Enabled";
constexpr char TEXT_CONFIGURATIONS[] = "Configurations";
constexpr char TEXT_BACK[] = "Back";
} // namespace

WifiStaSettingsMenu::WifiStaSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, WifiStaStatusText,               DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaMacText,                  DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaScanStatusText,           SwitchScreenAction<WifiStaScanMenu>>>();
    constructMenuItem<makeComponent<MenuItem, WifiSsidText,                    DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiBssidText,                   DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiRssiText,                    DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiAuthmodeText,                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiPairwiseCipherText,          DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiGroupCipherText,             DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaIpText,                   DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaNetmaskText,              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaGatewayText,              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaHostnameText,             DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaIpv6LinklocalText,        DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiStaIpv6GlobalText,           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLED>,        ToggleBoolAction, CheckboxIcon, WifiStaEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CONFIGURATIONS>, SwitchScreenAction<WifiStaConfigsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,           SwitchScreenAction<NetworkSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
}

std::string WifiStaSettingsMenu::text() const
{
    return "Sta Settings";
}

void WifiStaSettingsMenu::back()
{
    switchScreen<NetworkSettingsMenu>();
}
