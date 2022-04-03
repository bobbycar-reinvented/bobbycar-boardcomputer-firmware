#include "wifistatexthelpers.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <espwifistack.h>
#include <richtextrenderer.h>

// local includes
#include "wifiguiutils.h"

using namespace espgui;

std::string WifiStaStatusText::text() const
{
    const auto staStatus = wifi_stack::get_sta_status();
    return fmt::format("&sstatus: &f{}{}",
                       staStatus == wifi_stack::WiFiStaStatus::CONNECTED ? "&2" : "",
                       wifi_stack::toString(staStatus));
}

std::string WifiStaMacText::text() const
{
    std::string text = "&smac: &f";
    wifi_stack::mac_t mac;
    if (const auto result = esp_wifi_get_mac(WIFI_IF_STA, std::begin(mac)); result == ESP_OK)
        text += wifi_stack::toString(mac);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}

std::string WifiStaScanStatusText::text() const
{
    const auto status = wifi_stack::get_scan_status();
    return fmt::format("Scan {}{}",
                       status == wifi_stack::WiFiScanStatus::Finished ? "&2" : "",
                       wifi_stack::toString(status));
}

std::string WifiSsidText::text() const
{
    std::string text = "&sssid: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += richTextEscape(std::string_view{reinterpret_cast<const char*>(result->ssid)});
    return text;
}

std::string WifiBssidText::text() const
{
    std::string text = "&sbssid: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += wifi_stack::toString(wifi_stack::mac_t{result->bssid});
    return text;
}

std::string WifiRssiText::text() const
{
    std::string text = "&srssi: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += fmt::format("{}{}dB", rssiToColor(result->rssi), result->rssi);
    return text;
}

std::string WifiAuthmodeText::text() const
{
    std::string text = "&sauthmode: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += wifi_stack::toString(result->authmode);
    return text;
}

std::string WifiPairwiseCipherText::text() const
{
    std::string text = "&spairwCiph: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += wifi_stack::toString(result->pairwise_cipher);
    return text;
}

std::string WifiGroupCipherText::text() const
{
    std::string text = "&sgroupCiph: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            text += wifi_stack::toString(result->group_cipher);
    return text;
}

std::string WifiStaIpText::text() const
{
    std::string text = "&sip: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto result = wifi_stack::get_ip_info(wifi_stack::esp_netifs[ESP_IF_WIFI_STA]); result)
            text += wifi_stack::toString(result->ip);
    return text;
}

std::string WifiStaNetmaskText::text() const
{
    std::string text = "&smask: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto result = wifi_stack::get_ip_info(wifi_stack::esp_netifs[ESP_IF_WIFI_STA]); result)
            text += wifi_stack::toString(result->netmask);
    return text;
}

std::string WifiStaGatewayText::text() const
{
    std::string text = "&sgw: &f";
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto result = wifi_stack::get_ip_info(wifi_stack::esp_netifs[ESP_IF_WIFI_STA]); result)
            text += wifi_stack::toString(result->gw);
    return text;
}

std::string WifiStaHostnameText::text() const
{
    if (auto hostname = wifi_stack::get_hostname_for_interface(ESP_IF_WIFI_STA))
        return fmt::format("&shostname: &f{}", espgui::richTextEscape(*hostname));
    else
        return fmt::format("&shostname: &1{}", espgui::richTextEscape(std::move(hostname).error()));
}

std::string WifiStaIpv6LinklocalText::text() const
{
    std::string text = "&sipv6-loc: &f";
    esp_ip6_addr_t addr;
    if (const auto result = esp_netif_get_ip6_linklocal(wifi_stack::esp_netifs[ESP_IF_WIFI_STA], &addr); result == ESP_OK)
        text += wifi_stack::toString(addr);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}

std::string WifiStaIpv6GlobalText::text() const
{
    std::string text = "&sipv6-glo: &f";
    esp_ip6_addr_t addr;
    if (const auto result = esp_netif_get_ip6_global(wifi_stack::esp_netifs[ESP_IF_WIFI_STA], &addr); result == ESP_OK)
        text += wifi_stack::toString(addr);
    else
        text += fmt::format("&1{}", esp_err_to_name(result));
    return text;
}
