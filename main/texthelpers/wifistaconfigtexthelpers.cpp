#include "wifistaconfigtexthelpers.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <richtextrenderer.h>
#include <espwifiutils.h>

// local includes
#include "newsettings.h"

using namespace espgui;

std::string WifiStaConfigSsidText::text() const
{
    return fmt::format("&sssid: &f{}", richTextEscape(configs.wifi_configs[m_index].ssid.value));
}

std::string WifiStaConfigKeyText::text() const
{
    return fmt::format("&skey: &f{}", richTextEscape(configs.wifi_configs[m_index].key.value));
}

std::string WifiStaConfigStaticIpText::text() const
{
    return fmt::format("&sStatic Ip: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticIp.value));
}

std::string WifiStaConfigStaticSubnetText::text() const
{
    return fmt::format("&sStatic Mask: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticSubnet.value));
}

std::string WifiStaConfigStaticGatewayText::text() const
{
    return fmt::format("&sStatic Gw: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticGateway.value));
}

std::string WifiStaConfigStaticDns0Text::text() const
{
    return fmt::format("&sStatic Dns0: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticDns0.value));
}

std::string WifiStaConfigStaticDns1Text::text() const
{
    return fmt::format("&sStatic Dns1: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticDns1.value));
}

std::string WifiStaConfigStaticDns2Text::text() const
{
    return fmt::format("&sStatic Dns2: &f{}", wifi_stack::toString(configs.wifi_configs[m_index].staticDns2.value));
}
