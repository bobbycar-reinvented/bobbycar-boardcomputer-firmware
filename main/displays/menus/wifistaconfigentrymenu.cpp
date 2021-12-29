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
#include "newsettings.h"

using namespace espgui;

namespace {
constexpr char TEXT_USESTATICIP[] = "Use Static Ip";
constexpr char TEXT_USESTATICDNS[] = "Use Static Dns";
constexpr char TEXT_DELETECONFIG[] = "Delete config";
constexpr char TEXT_BACK[] = "Back";

class ClearConfigAction : public virtual espgui::ActionInterface
{
public:
    explicit ClearConfigAction(int index) : m_index{index} {}

    void triggered() override;

private:
    const int m_index;
};
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
    constructMenuItem<makeComponentArgs<MenuItem, ClearConfigAction,                 StaticText<TEXT_DELETECONFIG>>>(index);
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

namespace {
void ClearConfigAction::triggered()
{
    auto &config = configs.wifi_configs[m_index];
    configs.reset_config(config.ssid);
    configs.reset_config(config.key);
    configs.reset_config(config.useStaticIp);
    configs.reset_config(config.staticIp);
    configs.reset_config(config.staticSubnet);
    configs.reset_config(config.staticGateway);
    configs.reset_config(config.useStaticDns);
    configs.reset_config(config.staticDns0);
    configs.reset_config(config.staticDns1);
    configs.reset_config(config.staticDns2);
}
} // namespace
