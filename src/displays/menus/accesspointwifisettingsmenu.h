#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
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

// forward declares
namespace {
class WifiSettingsMenu;
} // namespace

namespace {
class AccessPointWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_ACCESSPOINTWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    AccessPointWifiSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAP>,                  WifiSoftApAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPDISCONNECT>,        WifiSoftApDisconnectAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPDISCONNECTWIFIOFF>, WifiSoftApDisconnectWifioffAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApGetStationNumText,                  StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApIpText,                             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApBroadcastIpText,                    StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApNetworkIdText,                      StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApSubnetCidrText,                     StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISOFTAPENABLEIPV6>,        WifiSoftApEnableIpV6Action>>();
        constructItem<makeComponent<MenuItem, WifiSoftApIpV6Text,                           StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApHostnameText,                       StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, WifiSoftApMacAddressText,                     StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                        SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
