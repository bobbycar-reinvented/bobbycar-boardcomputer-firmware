#pragma once

#include "sdkconfig.h"

// system includes
#include <array>
#include <optional>

// 3rdparty lib includes
#include <fmt/core.h>
#include <configmanager.h>
#include <configconstraints_base.h>
#include <configwrapper.h>
#include <espwifiutils.h>

//class WiFiConfig
//{
//public:
//    WiFiConfig(const char *ssidNvsKey, const char *keyNvsKey,
//               const char *useStaticIpKey, const char *staticIpKey, const char *staticSubnetKey, const char *staticGatewayKey,
//               const char *useStaticDnsKey, const char *staticDns0Key, const char *staticDns1Key, const char *staticDns2Key) :
//        ssid                                     {std::string{},                          DoReset,   StringMaxSize<32>,          ssidNvsKey                       },
//        key                                      {std::string{},                          DoReset,   StringOr<StringEmpty, StringMinMaxSize<8, 64>>, keyNvsKey    },
//        useStaticIp                              {false,                                  DoReset,   {},                         useStaticIpKey                   },
//        staticIp                                 {wifi_stack::ip_address_t{},             DoReset,   {},                         staticIpKey                      },
//        staticSubnet                             {wifi_stack::ip_address_t{},             DoReset,   {},                         staticSubnetKey                  },
//        staticGateway                            {wifi_stack::ip_address_t{},             DoReset,   {},                         staticGatewayKey                 },
//        useStaticDns                             {false,                                  DoReset,   {},                         useStaticDnsKey                  },
//        staticDns0                               {wifi_stack::ip_address_t{},             DoReset,   {},                         staticDns0Key                    },
//        staticDns1                               {wifi_stack::ip_address_t{},             DoReset,   {},                         staticDns1Key                    },
//        staticDns2                               {wifi_stack::ip_address_t{},             DoReset,   {},                         staticDns2Key                    }
//    {}

//    espconfig::ConfigWrapper<std::string> ssid;
//    espconfig::ConfigWrapper<std::string> key;
//    espconfig::ConfigWrapper<bool> useStaticIp;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticIp;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticSubnet;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticGateway;
//    espconfig::ConfigWrapper<bool> useStaticDns;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticDns0;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticDns1;
//    espconfig::ConfigWrapper<wifi_stack::ip_address_t> staticDns2;
//};
