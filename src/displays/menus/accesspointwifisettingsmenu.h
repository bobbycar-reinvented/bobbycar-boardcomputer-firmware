#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/wifisoftapaction.h"
#include "actions/wifisoftapdisconnectaction.h"
#include "actions/wifisoftapdisconnectwifioffaction.h"
#include "actions/wifisoftapenableipv6action.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "wifitexthelpers.h"
#include "texts.h"

namespace {
class WifiSettingsMenu;
}

namespace {
class AccessPointWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_ACCESSPOINTWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAP>,                  WifiSoftApAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPDISCONNECT>,        WifiSoftApDisconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPDISCONNECTWIFIOFF>, WifiSoftApDisconnectWifioffAction>,
        makeComponent<MenuItem, WifiSoftApGetStationNumText,                  StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApIpText,                             StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApBroadcastIpText,                    StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApNetworkIdText,                      StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApSubnetCidrText,                     StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPENABLEIPV6>,        WifiSoftApEnableIpV6Action>,
        makeComponent<MenuItem, WifiSoftApIpV6Text,                           StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApHostnameText,                       StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiSoftApMacAddressText,                     StaticFont<2>, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                        SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
