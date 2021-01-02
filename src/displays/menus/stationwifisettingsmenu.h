#pragma once

// Arduino includes
#include <WiFi.h>

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/wifireconnectaction.h"
#include "actions/wifidisconnectaction.h"
#include "actions/toggleboolaction.h"
#include "actions/wifienableipv6action.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "wifitexthelpers.h"
#include "wifiaccessors.h"
#include "texts.h"

// forward declares
namespace {
class WifiSettingsMenu;
} // namespace

namespace {
class StationWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_STATIONWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    StationWifiSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFIRECONNECT>,           WifiReconnectAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFIDISCONNECT>,          WifiDisconnectAction>>();
        constructItem<makeComponent<MenuItem, WifiIsConnectedText,                      StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTOCONNECT>,   ToggleBoolAction, CheckboxIcon, WifiAutoConnectAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTORECONNECT>, ToggleBoolAction, CheckboxIcon, WifiAutoReconnectAccessor>>();
        constructItem<makeComponent<MenuItem, WifiLocalIpText,                          StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiMacAddressText,                       StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSubnetMaskText,                       StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiGatewayIpText,                        StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiDnsIpText,                            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiBroadcastIpText,                      StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiNetworkIdText,                        StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSubnetCIDRText,                       StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFIENABLEIPV6>,          WifiEnableIpV6Action>>();
        constructItem<makeComponent<MenuItem, WifiLocalIpV6Text,                        StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiHostnameText,                         StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiStatusText,                           StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSsidText,                             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiPskText,                              StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiBssidText,                            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiRssiText,                             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
