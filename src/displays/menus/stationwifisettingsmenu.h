#pragma once

#include <WiFi.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
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

namespace {
class WifiSettingsMenu;
}

namespace {
class StationWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_STATIONWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_WIFIRECONNECT>,           WifiReconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIDISCONNECT>,          WifiDisconnectAction>,
        makeComponent<MenuItem, WifiIsConnectedText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTOCONNECT>,   ToggleBoolAction, CheckboxIcon, WifiAutoConnectAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEAUTORECONNECT>, ToggleBoolAction, CheckboxIcon, WifiAutoReconnectAccessor>,
        makeComponent<MenuItem, WifiLocalIpText,                          StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiMacAddressText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetMaskText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiGatewayIpText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiDnsIpText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBroadcastIpText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiNetworkIdText,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSubnetCIDRText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFIENABLEIPV6>,          WifiEnableIpV6Action>,
        makeComponent<MenuItem, WifiLocalIpV6Text,                        StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiHostnameText,                         StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiStatusText,                           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSsidText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiPskText,                              StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiBssidText,                            StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiRssiText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
