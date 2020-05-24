#pragma once

#include <WiFi.h>

#include "textinterface.h"
#include "utils.h"

namespace {
struct WifiStatusBitsText : public virtual TextInterface {
public:
    String text() const override { return String{"statusBits: "} + WiFi.getStatusBits(); }
};
struct WifiChannelText : public virtual TextInterface {
public:
    String text() const override { return String{"channel: "} + WiFi.channel(); }
};


struct WifiIsConnectedText : public virtual TextInterface {
public:
    String text() const override { return String{"isConnected: "} + toString(WiFi.isConnected()); }
};
struct WifiLocalIpText : public virtual TextInterface {
public:
    String text() const override { return String{"localIP: "} + WiFi.localIP().toString(); }
};
struct WifiMacAddressText : public virtual TextInterface {
public:
    String text() const override { return String{"macAddress: "} + WiFi.macAddress(); }
};
struct WifiSubnetMaskText : public virtual TextInterface {
public:
    String text() const override { return String{"subnetMask: "} + WiFi.subnetMask().toString(); }
};
struct WifiGatewayIpText : public virtual TextInterface {
public:
    String text() const override { return String{"gatewayIP: "} + WiFi.gatewayIP().toString(); }
};
struct WifiDnsIpText : public virtual TextInterface {
public:
    String text() const override { return String{"dnsIP: "} + WiFi.dnsIP().toString(); }
};
struct WifiBroadcastIpText : public virtual TextInterface {
public:
    String text() const override { return String{"broadcastIP: "} + WiFi.broadcastIP().toString(); }
};
struct WifiNetworkIdText : public virtual TextInterface {
public:
    String text() const override { return String{"networkID: "} + WiFi.networkID().toString(); }
};
struct WifiSubnetCIDRText : public virtual TextInterface {
public:
    String text() const override { return String{"subnetCIDR: "} + WiFi.subnetCIDR(); }
};
struct WifiLocalIpV6Text : public virtual TextInterface {
public:
    String text() const override { return String{"localIPv6: "} + WiFi.localIPv6().toString(); }
};
struct WifiHostnameText : public virtual TextInterface {
public:
    String text() const override { return String{"hostname: "} + WiFi.getHostname(); }
};
struct WifiStatusText : public virtual TextInterface {
public:
    String text() const override { return String{"status: "} + toString(WiFi.status()); }
};
struct WifiSsidText : public virtual TextInterface {
public:
    String text() const override { return String{"SSID: "} + WiFi.SSID(); }
};
struct WifiPskText : public virtual TextInterface {
public:
    String text() const override { return String{"psk: "} + WiFi.psk(); }
};
struct WifiBssidText : public virtual TextInterface {
public:
    String text() const override { return String{"BSSID: "} + WiFi.BSSIDstr(); }
};
struct WifiRssiText : public virtual TextInterface {
public:
    String text() const override { return String{"RSSI: "} + WiFi.RSSI(); }
};


class WifiSoftApGetStationNumText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPgetStationNum: "} + WiFi.softAPgetStationNum(); }
};
class WifiSoftApIpText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPIP: "} + WiFi.softAPIP().toString(); }
};
class WifiSoftApBroadcastIpText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPBroadcastIP: "} + WiFi.softAPBroadcastIP().toString(); }
};
class WifiSoftApNetworkIdText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPNetworkID: "} + WiFi.softAPNetworkID().toString(); }
};
class WifiSoftApSubnetCidrText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPSubnetCIDR: "} + WiFi.softAPSubnetCIDR(); }
};
class WifiSoftApIpV6Text : public virtual TextInterface {
public:
    String text() const override { return String{"softAPIPv6: "} + WiFi.softAPIPv6().toString(); }
};
class WifiSoftApHostnameText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPgetHostname: "} + WiFi.softAPgetHostname(); }
};
class WifiSoftApMacAddressText : public virtual TextInterface {
public:
    String text() const override { return String{"softAPmacAddress: "} + WiFi.softAPmacAddress(); }
};
}
