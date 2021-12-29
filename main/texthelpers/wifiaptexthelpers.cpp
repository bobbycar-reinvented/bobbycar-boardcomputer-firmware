#include "wifiaptexthelpers.h"

// esp-idf includes
#include <esp_wifi.h>

// 3rdparty lib includes
#include <fmt/core.h>
#include <espwifistack.h>
#include <richtextrenderer.h>

// local includes
#include "newsettings.h"
#include "wifi_bobbycar.h"

using namespace espgui;

std::string WifiApNameText::text() const
{
    return fmt::format("&sssid: &f{}", richTextEscape(configs.wifiApName.value));
}

std::string WifiApKeyText::text() const
{
    return fmt::format("&skey: &f{}", richTextEscape(configs.wifiApKey.value));
}

std::string WifiApMacText::text() const
{
    std::string text = "&smac: &f";
    wifi_stack::mac_t mac;
    if (const auto result = esp_wifi_get_mac(WIFI_IF_AP, std::begin(mac)); result == ESP_OK)
        text += wifi_stack::toString(mac);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}

std::string WifiApIpText::text() const
{
    return fmt::format("&sip: &f{}", wifi_stack::toString(apIP));
}

std::string WifiApMaskText::text() const
{
    return fmt::format("&smask: &f{}", wifi_stack::toString(netMsk));
}

std::string WifiApHostnameText::text() const
{
    if (auto hostname = wifi_stack::get_hostname_for_interface(ESP_IF_WIFI_AP))
        return fmt::format("&shostname: &f{}", espgui::richTextEscape(*hostname));
    else
        return fmt::format("&shostname: &1{}", espgui::richTextEscape(std::move(hostname).error()));
}

std::string WifiApClientsText::text() const
{
    wifi_sta_list_t clients;
    if (const auto result = esp_wifi_ap_get_sta_list(&clients); result == ESP_OK)
        return fmt::format("Clients ({})", clients.num);
    else
        return fmt::format("&7Clients &1{}", esp_err_to_name(result));
}
