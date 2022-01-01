#pragma once

#include "sdkconfig.h"

// system includes
#include <string>
#include <array>
#include <optional>

// esp-idf includes
#include <esp_sntp.h>

// 3rdparty lib includes
#include <fmt/core.h>
#include <configmanager.h>
#include <configconstraints_base.h>
#include <configconstraints_espchrono.h>
#include <configwrapper.h>
#include <espwifiutils.h>
#include <espchrono.h>
#include <makearray.h>

using namespace espconfig;

std::string defaultHostname();

constexpr const auto INPUT_MAPPING_NONE = std::numeric_limits<uint8_t>::max();

class WiFiConfig
{
public:
    WiFiConfig(const char *ssidNvsKey, const char *keyNvsKey,
               const char *useStaticIpKey, const char *staticIpKey, const char *staticSubnetKey, const char *staticGatewayKey,
               const char *useStaticDnsKey, const char *staticDns0Key, const char *staticDns1Key, const char *staticDns2Key) :
        ssid         {std::string{},              DoReset, StringMaxSize<32>,                              ssidNvsKey         },
        key          {std::string{},              DoReset, StringOr<StringEmpty, StringMinMaxSize<8, 64>>, keyNvsKey          },
        useStaticIp  {false,                      DoReset, {},                                             useStaticIpKey     },
        staticIp     {wifi_stack::ip_address_t{}, DoReset, {},                                             staticIpKey        },
        staticSubnet {wifi_stack::ip_address_t{}, DoReset, {},                                             staticSubnetKey    },
        staticGateway{wifi_stack::ip_address_t{}, DoReset, {},                                             staticGatewayKey   },
        useStaticDns {false,                      DoReset, {},                                             useStaticDnsKey    },
        staticDns0   {wifi_stack::ip_address_t{}, DoReset, {},                                             staticDns0Key      },
        staticDns1   {wifi_stack::ip_address_t{}, DoReset, {},                                             staticDns1Key      },
        staticDns2   {wifi_stack::ip_address_t{}, DoReset, {},                                             staticDns2Key      }
    {}

    ConfigWrapper<std::string> ssid;
    ConfigWrapper<std::string> key;
    ConfigWrapper<bool> useStaticIp;
    ConfigWrapper<wifi_stack::ip_address_t> staticIp;
    ConfigWrapper<wifi_stack::ip_address_t> staticSubnet;
    ConfigWrapper<wifi_stack::ip_address_t> staticGateway;
    ConfigWrapper<bool> useStaticDns;
    ConfigWrapper<wifi_stack::ip_address_t> staticDns0;
    ConfigWrapper<wifi_stack::ip_address_t> staticDns1;
    ConfigWrapper<wifi_stack::ip_address_t> staticDns2;
};

class WirelessDoorsConfig
{
public:
    WirelessDoorsConfig(const char *doorIdKey, const char *doorTokenKey) :
        doorId    {std::string{}, DoReset, StringMaxSize<24>, doorIdKey    },
        doorToken {std::string{}, DoReset, StringMaxSize<24>, doorTokenKey }
    {}

    ConfigWrapper<std::string> doorId;
    ConfigWrapper<std::string> doorToken;
};

class ConfiguredOtaServer
{
public:
    ConfiguredOtaServer(const char *nameKey, const char *urlKey) :
        name{std::string{}, DoReset, {},                                    nameKey },
        url {std::string{}, DoReset, StringOr<StringEmpty, StringValidUrl>, urlKey  }
    {}

    ConfigWrapper<std::string> name;
    ConfigWrapper<std::string> url;
};

class ConfigContainer
{
    using mac_t = wifi_stack::mac_t;

public:
    //                                            default                                 allowReset constraints                    nvsName
    ConfigWrapper<std::optional<mac_t>> baseMacAddressOverride{std::nullopt,              DoReset,   {},                            "baseMacAddrOver"     };
    ConfigWrapper<std::string> hostname           {defaultHostname,                       DoReset,   StringMinMaxSize<4, 32>,       "hostname"            };
    ConfigWrapper<bool>        wifiStaEnabled     {true,                                  DoReset,   {},                            "wifiStaEnabled"      };
    std::array<WiFiConfig, 10> wifi_configs {
        WiFiConfig {"wifi_ssid0", "wifi_key0", "wifi_usestatic0", "wifi_static_ip0", "wifi_stati_sub0", "wifi_stat_gate0", "wifi_usestadns0", "wifi_stat_dnsA0", "wifi_stat_dnsB0", "wifi_stat_dnsC0"},
        WiFiConfig {"wifi_ssid1", "wifi_key1", "wifi_usestatic1", "wifi_static_ip1", "wifi_stati_sub1", "wifi_stat_gate1", "wifi_usestadns1", "wifi_stat_dnsA1", "wifi_stat_dnsB1", "wifi_stat_dnsC1"},
        WiFiConfig {"wifi_ssid2", "wifi_key2", "wifi_usestatic2", "wifi_static_ip2", "wifi_stati_sub2", "wifi_stat_gate2", "wifi_usestadns2", "wifi_stat_dnsA2", "wifi_stat_dnsB2", "wifi_stat_dnsC2"},
        WiFiConfig {"wifi_ssid3", "wifi_key3", "wifi_usestatic3", "wifi_static_ip3", "wifi_stati_sub3", "wifi_stat_gate3", "wifi_usestadns3", "wifi_stat_dnsA3", "wifi_stat_dnsB3", "wifi_stat_dnsC3"},
        WiFiConfig {"wifi_ssid4", "wifi_key4", "wifi_usestatic4", "wifi_static_ip4", "wifi_stati_sub4", "wifi_stat_gate4", "wifi_usestadns4", "wifi_stat_dnsA4", "wifi_stat_dnsB4", "wifi_stat_dnsC4"},
        WiFiConfig {"wifi_ssid5", "wifi_key5", "wifi_usestatic5", "wifi_static_ip5", "wifi_stati_sub5", "wifi_stat_gate5", "wifi_usestadns5", "wifi_stat_dnsA5", "wifi_stat_dnsB5", "wifi_stat_dnsC5"},
        WiFiConfig {"wifi_ssid6", "wifi_key6", "wifi_usestatic6", "wifi_static_ip6", "wifi_stati_sub6", "wifi_stat_gate6", "wifi_usestadns6", "wifi_stat_dnsA6", "wifi_stat_dnsB6", "wifi_stat_dnsC6"},
        WiFiConfig {"wifi_ssid7", "wifi_key7", "wifi_usestatic7", "wifi_static_ip7", "wifi_stati_sub7", "wifi_stat_gate7", "wifi_usestadns7", "wifi_stat_dnsA7", "wifi_stat_dnsB7", "wifi_stat_dnsC7"},
        WiFiConfig {"wifi_ssid8", "wifi_key8", "wifi_usestatic8", "wifi_static_ip8", "wifi_stati_sub8", "wifi_stat_gate8", "wifi_usestadns8", "wifi_stat_dnsA8", "wifi_stat_dnsB8", "wifi_stat_dnsC8"},
        WiFiConfig {"wifi_ssid9", "wifi_key9", "wifi_usestatic9", "wifi_static_ip9", "wifi_stati_sub9", "wifi_stat_gate9", "wifi_usestadns9", "wifi_stat_dnsA9", "wifi_stat_dnsB9", "wifi_stat_dnsC9"}
    };
    ConfigWrapper<int8_t>      wifiStaMinRssi     {-90,                                    DoReset,   {},                           "wifiStaMinRssi"      };

    ConfigWrapper<bool>        wifiApEnabled      {true,                                   DoReset,   {},                           "wifiApEnabled"       };
    ConfigWrapper<std::string> wifiApName         {defaultHostname,                        DoReset,   StringMinMaxSize<4, 32>,      "wifiApName"          };
    ConfigWrapper<std::string> wifiApKey          {"Passwort_123",                         DoReset,   StringOr<StringEmpty, StringMinMaxSize<8, 64>>, "wifiApKey" };
    ConfigWrapper<wifi_stack::ip_address_t> wifiApIp{wifi_stack::ip_address_t{10, 0, 0, 1},DoReset,   {},                           "wifiApIp"            };
    ConfigWrapper<wifi_stack::ip_address_t> wifiApMask{wifi_stack::ip_address_t{255, 255, 255, 0},DoReset, {},                      "wifiApMask"          };
    ConfigWrapper<uint8_t>     wifiApChannel      {1,                                      DoReset,   MinMaxValue<uint8_t, 1, 14>,  "wifiApChannel"       };
    ConfigWrapper<wifi_auth_mode_t> wifiApAuthmode{WIFI_AUTH_WPA2_PSK,                     DoReset,   {},                           "wifiApAuthmode"      };

    ConfigWrapper<bool>     timeServerEnabled     {true,                                   DoReset,   {},                           "timeServerEnabl"     };
    ConfigWrapper<std::string>   timeServer       {"europe.pool.ntp.org",                  DoReset,   StringMaxSize<64>,            "timeServer"          };
    ConfigWrapper<sntp_sync_mode_t> timeSyncMode  {SNTP_SYNC_MODE_IMMED,                   DoReset,   {},                           "timeSyncMode"        };
    ConfigWrapper<espchrono::milliseconds32> timeSyncInterval{espchrono::milliseconds32{CONFIG_LWIP_SNTP_UPDATE_DELAY}, DoReset, MinTimeSyncInterval, "timeSyncInterva" };
    ConfigWrapper<espchrono::minutes32> timezoneOffset{espchrono::minutes32{60},           DoReset,   {},                           "timezoneOffset"      }; // MinMaxValue<minutes32, -1440m, 1440m>
    ConfigWrapper<espchrono::DayLightSavingMode>timeDst{espchrono::DayLightSavingMode::EuropeanSummerTime, DoReset, {},             "time_dst"            };

    ConfigWrapper<bool>           canResetOnError {false,                                  DoReset,   {},                           "canBusRstErr"        };

    ConfigWrapper<int16_t>     sampleCount        {50,                                     DoReset,   {},                           "sampleCount"         };
    ConfigWrapper<int16_t>     gasMin             {0,                                      DoReset,  MinMaxValue<int16_t, 0, 4095>, "gasMin"              };
    ConfigWrapper<int16_t>     gasMax             {4095,                                   DoReset,  MinMaxValue<int16_t, 0, 4095>, "gasMax"              };
    ConfigWrapper<int16_t>     bremsMin           {0,                                      DoReset,  MinMaxValue<int16_t, 0, 4095>, "bremsMin"            };
    ConfigWrapper<int16_t>     bremsMax           {4096,                                   DoReset,  MinMaxValue<int16_t, 0, 4095>, "bremsMax"            };

    ConfigWrapper<uint8_t>     dpadDebounce       {25,                                     DoReset,   {},                           "dpadDebounce"        };

    ConfigWrapper<uint8_t>     dpadMappingLeft    {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapLeft"         };
    ConfigWrapper<uint8_t>     dpadMappingRight   {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapRight"        };
    ConfigWrapper<uint8_t>     dpadMappingUp      {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapUp"           };
    ConfigWrapper<uint8_t>     dpadMappingDown    {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapDown"         };
    ConfigWrapper<uint8_t>     dpadMappingProfile0{INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapProfile0"     };
    ConfigWrapper<uint8_t>     dpadMappingProfile1{INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapProfile1"     };
    ConfigWrapper<uint8_t>     dpadMappingProfile2{INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapProfile2"     };
    ConfigWrapper<uint8_t>     dpadMappingProfile3{INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapProfile3"     };
    ConfigWrapper<uint8_t>     dpadMappingLeft2   {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapLeft2"        };
    ConfigWrapper<uint8_t>     dpadMappingRight2  {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapRight2"       };
    ConfigWrapper<uint8_t>     dpadMappingUp2     {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapUp2"          };
    ConfigWrapper<uint8_t>     dpadMappingDown2   {INPUT_MAPPING_NONE,                     DoReset,   {},                           "dpadMapDown2"        };

    std::array<WirelessDoorsConfig, 5> wireless_door_configs {
        WirelessDoorsConfig { "door_id0", "door_token0" },
        WirelessDoorsConfig { "door_id1", "door_token1" },
        WirelessDoorsConfig { "door_id2", "door_token2" },
        WirelessDoorsConfig { "door_id3", "door_token3" },
        WirelessDoorsConfig { "door_id4", "door_token4" }
    };

    ConfigWrapper<std::string> bluetoothName      {defaultHostname,                        DoReset,   StringMinMaxSize<4, 32>,    "bluetoothName"       };

    ConfigWrapper<bool>        reverseBeep        {false,                                  DoReset,   {},                         "reverseBeep"         };
    ConfigWrapper<uint8_t>     reverseBeepFreq0   {3,                                      DoReset,   {},                         "revBeepFreq0"        };
    ConfigWrapper<uint8_t>     reverseBeepFreq1   {0,                                      DoReset,   {},                         "revBeepFreq1"        };
    ConfigWrapper<int16_t>     reverseBeepDuration0{500,                                   DoReset,   {},                         "revBeepDur0"         };
    ConfigWrapper<int16_t>     reverseBeepDuration1{500,                                   DoReset,   {},                         "revBeepDur1"         };

    ConfigWrapper<std::string> cloudUrl           {std::string{},                          DoReset,   StringOr<StringEmpty, StringValidUrl>, "cloudUrl" };
    ConfigWrapper<std::string> udpCloudHost       {std::string{},                          DoReset,   {},                         "udpCloudHost"        };

    ConfigWrapper<std::string> otaUrl             {std::string{},                          DoReset,   StringOr<StringEmpty, StringValidUrl>, "otaUrl"   };
    ConfigWrapper<std::string> otaUsername        {std::string{},                          DoReset,   {},                         "otaUsername"         };
    ConfigWrapper<std::string> otaServerUrl       {std::string{},                          DoReset,   StringOr<StringEmpty, StringValidUrl>, "otaServerUrl" };
    ConfigWrapper<std::string> otaServerBranch    {std::string{},                          DoReset,   {},                         "otaServerBranch"     };
    std::array<ConfiguredOtaServer, 5> otaServers {
        ConfiguredOtaServer { "otaName0", "otaUrl0" },
        ConfiguredOtaServer { "otaName1", "otaUrl1" },
        ConfiguredOtaServer { "otaName2", "otaUrl2" },
        ConfiguredOtaServer { "otaName3", "otaUrl3" },
        ConfiguredOtaServer { "otaName4", "otaUrl4" }
    };

    ConfigWrapper<bool>        dns_announce_enabled{true,                                  DoReset,   {},                         "dnsAnnounceEnab"     };
    ConfigWrapper<std::string> dns_announce_key   {std::string{},                          DoReset,   {},                         "dnsAnnounceKey"      };
    ConfigWrapper<std::string> webserverPassword  {std::string{},                          DoReset,   {},                         "websPassword"        };

    ConfigWrapper<uint32_t> ledStripMaxMilliamps  {3000,                                   DoReset,   {},                         "ledMaxMilliamps"     };

#define NEW_SETTINGS(x) \
    x(baseMacAddressOverride) \
    x(hostname) \
    \
    x(wifiStaEnabled) \
    x(wifi_configs[0].ssid) \
    x(wifi_configs[0].key) \
    x(wifi_configs[0].useStaticIp) \
    x(wifi_configs[0].staticIp) \
    x(wifi_configs[0].staticSubnet) \
    x(wifi_configs[0].staticGateway) \
    x(wifi_configs[0].useStaticDns) \
    x(wifi_configs[0].staticDns0) \
    x(wifi_configs[0].staticDns1) \
    x(wifi_configs[0].staticDns2) \
    x(wifi_configs[1].ssid) \
    x(wifi_configs[1].key) \
    x(wifi_configs[1].useStaticIp) \
    x(wifi_configs[1].staticIp) \
    x(wifi_configs[1].staticSubnet) \
    x(wifi_configs[1].staticGateway) \
    x(wifi_configs[1].useStaticDns) \
    x(wifi_configs[1].staticDns0) \
    x(wifi_configs[1].staticDns1) \
    x(wifi_configs[1].staticDns2) \
    x(wifi_configs[2].ssid) \
    x(wifi_configs[2].key) \
    x(wifi_configs[2].useStaticIp) \
    x(wifi_configs[2].staticIp) \
    x(wifi_configs[2].staticSubnet) \
    x(wifi_configs[2].staticGateway) \
    x(wifi_configs[2].useStaticDns) \
    x(wifi_configs[2].staticDns0) \
    x(wifi_configs[2].staticDns1) \
    x(wifi_configs[2].staticDns2) \
    x(wifi_configs[3].ssid) \
    x(wifi_configs[3].key) \
    x(wifi_configs[3].useStaticIp) \
    x(wifi_configs[3].staticIp) \
    x(wifi_configs[3].staticSubnet) \
    x(wifi_configs[3].staticGateway) \
    x(wifi_configs[3].useStaticDns) \
    x(wifi_configs[3].staticDns0) \
    x(wifi_configs[3].staticDns1) \
    x(wifi_configs[3].staticDns2) \
    x(wifi_configs[4].ssid) \
    x(wifi_configs[4].key) \
    x(wifi_configs[4].useStaticIp) \
    x(wifi_configs[4].staticIp) \
    x(wifi_configs[4].staticSubnet) \
    x(wifi_configs[4].staticGateway) \
    x(wifi_configs[4].useStaticDns) \
    x(wifi_configs[4].staticDns0) \
    x(wifi_configs[4].staticDns1) \
    x(wifi_configs[4].staticDns2) \
    x(wifi_configs[5].ssid) \
    x(wifi_configs[5].key) \
    x(wifi_configs[5].useStaticIp) \
    x(wifi_configs[5].staticIp) \
    x(wifi_configs[5].staticSubnet) \
    x(wifi_configs[5].staticGateway) \
    x(wifi_configs[5].useStaticDns) \
    x(wifi_configs[5].staticDns0) \
    x(wifi_configs[5].staticDns1) \
    x(wifi_configs[5].staticDns2) \
    x(wifi_configs[6].ssid) \
    x(wifi_configs[6].key) \
    x(wifi_configs[6].useStaticIp) \
    x(wifi_configs[6].staticIp) \
    x(wifi_configs[6].staticSubnet) \
    x(wifi_configs[6].staticGateway) \
    x(wifi_configs[6].useStaticDns) \
    x(wifi_configs[6].staticDns0) \
    x(wifi_configs[6].staticDns1) \
    x(wifi_configs[6].staticDns2) \
    x(wifi_configs[7].ssid) \
    x(wifi_configs[7].key) \
    x(wifi_configs[7].useStaticIp) \
    x(wifi_configs[7].staticIp) \
    x(wifi_configs[7].staticSubnet) \
    x(wifi_configs[7].staticGateway) \
    x(wifi_configs[7].useStaticDns) \
    x(wifi_configs[7].staticDns0) \
    x(wifi_configs[7].staticDns1) \
    x(wifi_configs[7].staticDns2) \
    x(wifi_configs[8].ssid) \
    x(wifi_configs[8].key) \
    x(wifi_configs[8].useStaticIp) \
    x(wifi_configs[8].staticIp) \
    x(wifi_configs[8].staticSubnet) \
    x(wifi_configs[8].staticGateway) \
    x(wifi_configs[8].useStaticDns) \
    x(wifi_configs[8].staticDns0) \
    x(wifi_configs[8].staticDns1) \
    x(wifi_configs[8].staticDns2) \
    x(wifi_configs[9].ssid) \
    x(wifi_configs[9].key) \
    x(wifi_configs[9].useStaticIp) \
    x(wifi_configs[9].staticIp) \
    x(wifi_configs[9].staticSubnet) \
    x(wifi_configs[9].staticGateway) \
    x(wifi_configs[9].useStaticDns) \
    x(wifi_configs[9].staticDns0) \
    x(wifi_configs[9].staticDns1) \
    x(wifi_configs[9].staticDns2) \
    \
    x(wifiStaMinRssi) \
    \
    x(wifiApEnabled) \
    x(wifiApName) \
    x(wifiApKey) \
    x(wifiApIp) \
    x(wifiApMask) \
    x(wifiApChannel) \
    x(wifiApAuthmode) \
    \
    x(timeServerEnabled) \
    x(timeServer) \
    x(timeSyncMode) \
    x(timeSyncInterval) \
    x(timezoneOffset) \
    x(timeDst) \
    \
    x(canResetOnError) \
    \
    x(sampleCount) \
    x(gasMin) \
    x(gasMax) \
    x(bremsMin) \
    x(bremsMax) \
    \
    x(dpadDebounce) \
    \
    x(dpadMappingLeft) \
    x(dpadMappingRight) \
    x(dpadMappingUp) \
    x(dpadMappingDown) \
    x(dpadMappingProfile0) \
    x(dpadMappingProfile1) \
    x(dpadMappingProfile2) \
    x(dpadMappingProfile3) \
    x(dpadMappingLeft2) \
    x(dpadMappingRight2) \
    x(dpadMappingUp2) \
    x(dpadMappingDown2) \
    \
    x(wireless_door_configs[0].doorId) \
    x(wireless_door_configs[0].doorToken) \
    x(wireless_door_configs[1].doorId) \
    x(wireless_door_configs[1].doorToken) \
    x(wireless_door_configs[2].doorId) \
    x(wireless_door_configs[2].doorToken) \
    x(wireless_door_configs[3].doorId) \
    x(wireless_door_configs[3].doorToken) \
    x(wireless_door_configs[4].doorId) \
    x(wireless_door_configs[4].doorToken) \
    \
    x(bluetoothName) \
    \
    x(reverseBeep) \
    x(reverseBeepFreq0) \
    x(reverseBeepFreq1) \
    x(reverseBeepDuration0) \
    x(reverseBeepDuration1) \
    \
    x(cloudUrl) \
    x(udpCloudHost) \
    \
    x(otaUrl) \
    x(otaUsername) \
    x(otaServerUrl) \
    x(otaServerBranch) \
    x(otaServers[0].name) \
    x(otaServers[0].url) \
    x(otaServers[1].name) \
    x(otaServers[1].url) \
    x(otaServers[2].name) \
    x(otaServers[2].url) \
    x(otaServers[3].name) \
    x(otaServers[3].url) \
    x(otaServers[4].name) \
    x(otaServers[4].url) \
    \
    x(dns_announce_enabled) \
    x(dns_announce_key) \
    x(webserverPassword) \
    \
    //x(ledStripMaxMilliamps)

    template<typename T>
    void callForEveryConfig(T &&callback)
    {
#define HELPER(x) callback(x);
        NEW_SETTINGS(HELPER)
#undef HELPER
        callback(ledStripMaxMilliamps);
    }

    auto getAllConfigParams()
    {
        return cpputils::make_array(
#define HELPER(x) std::ref<ConfigWrapperInterface>(x),
            NEW_SETTINGS(HELPER)
#undef HELPER
            std::ref<ConfigWrapperInterface>(ledStripMaxMilliamps)
        );
    }
};

extern ConfigManager<ConfigContainer> configs;
