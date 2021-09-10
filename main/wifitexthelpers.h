#pragma once

// 3rdparty lib includes
#include <fmt/core.h>
#include <espwifistack.h>
#include <esp_netif.h>
#include <lwip/dns.h>

// local includes
#include "textinterface.h"

namespace {
class WifiStatusText : public virtual TextInterface { public: std::string text() const override {
    return fmt::format("Status: {}", wifi_stack::toString(wifi_stack::get_sta_status())); }};

class WifiScanStatusText : public virtual TextInterface { public: std::string text() const override {
    return fmt::format("ScanStatus: {}", wifi_stack::toString(wifi_stack::get_scan_status())); }};

class WifiHostnameText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "Hostname: ";
        const char *hostname{};
        if (const auto result = esp_netif_get_hostname(wifi_stack::esp_netifs[ESP_IF_WIFI_STA], &hostname); result == ESP_OK)
            if (hostname)
                text += hostname;
        return text;
    }
};

class WifiMacText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "MAC: ";
        if (const auto result = wifi_stack::get_base_mac_addr())
            text += wifi_stack::toString(*result);
        return text;
    }
};

class WifiSsidText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "SSID: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += std::string_view{reinterpret_cast<const char*>(result->ssid)};
        return text;
    }
};

class WifiBssidText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "BSSID: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += wifi_stack::toString(wifi_stack::mac_t{result->bssid});
        return text;
    }
};

class WifiRssiText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "RSSI: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += fmt::format("{}dB", result->rssi);
        return text;
    }
};

class WifiEncryptionTypeText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "encryptionType: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += wifi_stack::toString(result->authmode);
        return text;
    }
};

class WifiPairwiseCipherText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "pairwiseCipher: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += wifi_stack::toString(result->pairwise_cipher);
        return text;
    }
};

class WifiGroupCipherText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "groupCipher: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                text += wifi_stack::toString(result->group_cipher);
        return text;
    }
};

class WifiIpText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "ip: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto result = wifi_stack::get_ip_info(TCPIP_ADAPTER_IF_STA); result)
                text += wifi_stack::toString(result->ip);
        return text;
    }
};

class WifiNetmaskText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "netmask: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto result = wifi_stack::get_ip_info(TCPIP_ADAPTER_IF_STA); result)
                text += wifi_stack::toString(result->netmask);
        return text;
    }
};

class WifiGatewayText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "gateway: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto result = wifi_stack::get_ip_info(TCPIP_ADAPTER_IF_STA); result)
                text += wifi_stack::toString(result->gw);
        return text;
    }
};

class WifiIpv6LinklocalText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "ipv6: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        {
            esp_ip6_addr_t addr;
            if (const auto result = esp_netif_get_ip6_linklocal(wifi_stack::esp_netifs[ESP_IF_WIFI_STA], &addr); result == ESP_OK)
                text += wifi_stack::toString(addr);
        }
        return text;
    }
};

class WifiIpv6GlobalText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "ipv6: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        {
            esp_ip6_addr_t addr;
            if (const auto result = esp_netif_get_ip6_global(wifi_stack::esp_netifs[ESP_IF_WIFI_STA], &addr); result == ESP_OK)
                text += wifi_stack::toString(addr);
        }
        return text;
    }
};

class WifiDns0Text : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "dns0: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const ip_addr_t *dns_ip = dns_getserver(0))
                text += wifi_stack::toString(*dns_ip);
        return text;
    }
};

class WifiDns1Text : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "dns1: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const ip_addr_t *dns_ip = dns_getserver(1))
                text += wifi_stack::toString(*dns_ip);
        return text;
    }
};

class WifiDns2Text : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "dns2: ";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const ip_addr_t *dns_ip = dns_getserver(2))
                text += wifi_stack::toString(*dns_ip);
        return text;
    }
};

constexpr char TEXT_SOFTAPGETSTATIONNUM[] = "softAPgetStationNum: ";
using WifiSoftApGetStationNumText = StaticText<TEXT_SOFTAPGETSTATIONNUM>; //StatusTextHelper<TEXT_SOFTAPGETSTATIONNUM, &WiFi.softAPgetStationNum>
constexpr char TEXT_SOFTAPIP[] = "softAPIP: ";
using WifiSoftApIpText = StaticText<TEXT_SOFTAPIP>; //StatusTextHelper<TEXT_SOFTAPIP, &WiFi.softAPIP>
constexpr char TEXT_SOFTAPBROADCASTIP[] = "softAPBroadcastIP: ";
using WifiSoftApBroadcastIpText = StaticText<TEXT_SOFTAPBROADCASTIP>; //StatusTextHelper<TEXT_SOFTAPBROADCASTIP, &WiFi.softAPBroadcastIP>
constexpr char TEXT_SOFTAPNETWORKID[] = "softAPNetworkID: ";
using WifiSoftApNetworkIdText = StaticText<TEXT_SOFTAPNETWORKID>; //StatusTextHelper<TEXT_SOFTAPNETWORKID, &WiFi.softAPNetworkID>
constexpr char TEXT_SOFTAPSUBNETCIDR[] = "softAPSubnetCIDR: ";
using WifiSoftApSubnetCidrText = StaticText<TEXT_SOFTAPSUBNETCIDR>; //StatusTextHelper<TEXT_SOFTAPSUBNETCIDR, &WiFi.softAPSubnetCIDR>
constexpr char TEXT_SOFTAPIPV6[] = "softAPIPv6: ";
using WifiSoftApIpV6Text = StaticText<TEXT_SOFTAPIPV6>; //StatusTextHelper<TEXT_SOFTAPIPV6, &WiFi.softAPIPv6>
constexpr char TEXT_SOFTAPGETHOSTNAME[] = "softAPgetHostname: ";
using WifiSoftApHostnameText = StaticText<TEXT_SOFTAPGETHOSTNAME>; //StatusTextHelper<TEXT_SOFTAPGETHOSTNAME, &WiFi.softAPgetHostname>
constexpr char TEXT_SOFTAPMACADDRESS[] = "softAPmacAddress: ";
using WifiSoftApMacAddressText = StaticText<TEXT_SOFTAPMACADDRESS>; //StatusTextHelper<TEXT_SOFTAPMACADDRESS, &WiFi.softAPmacAddress>
}
