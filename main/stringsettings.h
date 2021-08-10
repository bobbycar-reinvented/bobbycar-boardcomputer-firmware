#pragma once

// system includes
#include <array>
#include <string>

namespace {
struct StringSettings
{
    struct ConfiguredWifi {
        std::string ssid;
        std::string key;
    };

    std::array<ConfiguredWifi, 10> wifis;

#ifdef FEATURE_CLOUD
    std::string cloudUrl;
#endif


    template<typename T>
    void executeForEveryCommonSetting(T &&callable);

    template<typename T>
    void executeForEveryProfileSetting(T &&callable);
};

template<typename T>
void StringSettings::executeForEveryCommonSetting(T &&callable)
{
    callable("ssid0", wifis[0].ssid);
    callable("key0", wifis[0].key);
    callable("ssid1", wifis[1].ssid);
    callable("key1", wifis[1].key);
    callable("ssid2", wifis[2].ssid);
    callable("key2", wifis[2].key);
    callable("ssid3", wifis[3].ssid);
    callable("key3", wifis[3].key);
    callable("ssid4", wifis[4].ssid);
    callable("key4", wifis[4].key);
    callable("ssid5", wifis[5].ssid);
    callable("key5", wifis[5].key);
    callable("ssid6", wifis[6].ssid);
    callable("key6", wifis[6].key);
    callable("ssid7", wifis[7].ssid);
    callable("key7", wifis[7].key);
    callable("ssid8", wifis[8].ssid);
    callable("key8", wifis[8].key);
    callable("ssid9", wifis[9].ssid);
    callable("key9", wifis[9].key);

#ifdef FEATURE_CLOUD
    callable("cloudUrl", cloudUrl);
#endif
}

template<typename T>
void StringSettings::executeForEveryProfileSetting(T &&callable)
{
}
}
