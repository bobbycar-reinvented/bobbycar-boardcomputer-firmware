#include "networktexthelpers.h"

// esp-idf
#include <esp_system.h>
#include <esp_mac.h>
#include <lwip/dns.h>

// 3rdparty lib includes
#include <espwifistack.h>
#include <espwifiutils.h>
#include <fmt/format.h>

using namespace espgui;

std::string WifiDefaultMacText::text() const
{
    std::string text = "&sdefault-mac: &f";
    wifi_stack::mac_t mac;
    if (const auto result = esp_efuse_mac_get_default(std::begin(mac)); result == ESP_OK)
        text += wifi_stack::toString(mac);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}

std::string WifiBaseMacText::text() const
{
    std::string text = "&sbase-mac: &f";
    wifi_stack::mac_t mac;
    if (const auto result = esp_base_mac_addr_get(std::begin(mac)); result == ESP_OK)
        text += wifi_stack::toString(mac);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}

std::string DnsText::text() const
{
    std::string text = fmt::format("&sdns{}: &f", m_index);
    if (const ip_addr_t *dns_ip = dns_getserver(m_index))
        text += wifi_stack::toString(*dns_ip);
    return text;
}

std::string WifiTxPowerText::text() const
{
    int8_t power;
    if(const auto err = esp_wifi_get_max_tx_power(&power); err == ESP_OK)
        return fmt::format("&stx-power: {:.2f} dBm ({})&f", power * 0.25f, power);
    return "";
}
