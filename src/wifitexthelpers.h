#pragma once

#include <WiFi.h>

#include "textinterface.h"
#include "utils.h"

namespace {
struct WifiStatusBitsText : public virtual TextInterface {
public:
    std::string text() const override { return "statusBits: " + std::to_string(WiFi.getStatusBits()); }
};
struct WifiChannelText : public virtual TextInterface {
public:
    std::string text() const override { return "channel: " + std::to_string(WiFi.channel()); }
};


struct WifiIsConnectedText : public virtual TextInterface {
public:
    std::string text() const override { return "isConnected: " + std::to_string(WiFi.isConnected()); }
};
struct WifiLocalIpText : public virtual TextInterface {
public:
    std::string text() const override { return "localIP: " + to_string(WiFi.localIP()); }
};
struct WifiMacAddressText : public virtual TextInterface {
public:
    std::string text() const override { return "macAddress: " + to_string(WiFi.macAddress()); }
};
struct WifiSubnetMaskText : public virtual TextInterface {
public:
    std::string text() const override { return "subnetMask: " + to_string(WiFi.subnetMask()); }
};
struct WifiGatewayIpText : public virtual TextInterface {
public:
    std::string text() const override { return "gatewayIP: " + to_string(WiFi.gatewayIP()); }
};
struct WifiDnsIpText : public virtual TextInterface {
public:
    std::string text() const override { return "dnsIP: " + to_string(WiFi.dnsIP()); }
};
struct WifiBroadcastIpText : public virtual TextInterface {
public:
    std::string text() const override { return "broadcastIP: " + to_string(WiFi.broadcastIP()); }
};
struct WifiNetworkIdText : public virtual TextInterface {
public:
    std::string text() const override { return "networkID: " + to_string(WiFi.networkID()); }
};
struct WifiSubnetCIDRText : public virtual TextInterface {
public:
    std::string text() const override { return "subnetCIDR: " + to_string(WiFi.subnetCIDR()); }
};
struct WifiLocalIpV6Text : public virtual TextInterface {
public:
    std::string text() const override { return "localIPv6: " + to_string(WiFi.localIPv6()); }
};
struct WifiHostnameText : public virtual TextInterface {
public:
    std::string text() const override { return "hostname: " + to_string(WiFi.getHostname()); }
};
struct WifiStatusText : public virtual TextInterface {
public:
    std::string text() const override { return "status: " + to_string(WiFi.status()); }
};
struct WifiSsidText : public virtual TextInterface {
public:
    std::string text() const override { return "SSID: " + to_string(WiFi.SSID()); }
};
struct WifiPskText : public virtual TextInterface {
public:
    std::string text() const override { return "psk: " + to_string(WiFi.psk()); }
};
struct WifiBssidText : public virtual TextInterface {
public:
    std::string text() const override { return "BSSID: " + to_string(WiFi.BSSIDstr()); }
};
struct WifiRssiText : public virtual TextInterface {
public:
    std::string text() const override { return "RSSI: " + to_string(WiFi.RSSI()); }
};


class WifiSoftApGetStationNumText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPgetStationNum: " + to_string(WiFi.softAPgetStationNum()); }
};
class WifiSoftApIpText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPIP: " + to_string(WiFi.softAPIP()); }
};
class WifiSoftApBroadcastIpText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPBroadcastIP: " + to_string(WiFi.softAPBroadcastIP()); }
};
class WifiSoftApNetworkIdText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPNetworkID: " + to_string(WiFi.softAPNetworkID()); }
};
class WifiSoftApSubnetCidrText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPSubnetCIDR: " + std::to_string(WiFi.softAPSubnetCIDR()); }
};
class WifiSoftApIpV6Text : public virtual TextInterface {
public:
    std::string text() const override { return "softAPIPv6: " + to_string(WiFi.softAPIPv6()); }
};
class WifiSoftApHostnameText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPgetHostname: " + to_string(WiFi.softAPgetHostname()); }
};
class WifiSoftApMacAddressText : public virtual TextInterface {
public:
    std::string text() const override { return "softAPmacAddress: " + to_string(WiFi.softAPmacAddress()); }
};
}
