#include "wifistaconfigentrymenu.h"

// 3rdparty lib includes
#include <menuitem.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <icons/back.h>
#include <screenmanager.h>
#include <actions/toggleboolaction.h>
#include <checkboxicon.h>

// local includes
#include "texthelpers/wifistaconfigtexthelpers.h"
#include "accessors/wifistaconfigaccessors.h"
#include "wifistaconfigsmenu.h"

using namespace espgui;

namespace {
constexpr char TEXT_USESTATICIP[] = "Use Static Ip";
constexpr char TEXT_USESTATICDNS[] = "Use Static Dns";
constexpr char TEXT_BACK[] = "Back";
} // namespace

WifiStaConfigEntryMenu::WifiStaConfigEntryMenu(int index) :
    m_index{index}
{
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigSsidText,             DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigKeyText,              DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigUseStaticIpAccessor,  StaticText<TEXT_USESTATICIP>, ToggleBoolAction, CheckboxIcon>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticIpText,         DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticSubnetText,     DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticGatewayText,    DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigUseStaticDnsAccessor, StaticText<TEXT_USESTATICDNS>, ToggleBoolAction, CheckboxIcon>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticDns0Text,       DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticDns1Text,       DummyAction>>(index);
    constructMenuItem<makeComponentArgs<MenuItem, WifiStaConfigStaticDns2Text,       DummyAction>>(index);
    constructMenuItem<makeComponent<MenuItem,     StaticText<TEXT_BACK>,             SwitchScreenAction<WifiStaConfigsMenu>, StaticMenuItemIcon<&icons::back>>>();
}

std::string WifiStaConfigEntryMenu::text() const
{
    return fmt::format("Wifi Config {}", m_index + 1);
}

void WifiStaConfigEntryMenu::back()
{
    switchScreen<WifiStaConfigsMenu>();
}
