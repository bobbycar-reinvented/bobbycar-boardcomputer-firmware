#include "wifi_bobbycar.h"

// system includes
#include <optional>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espwifistack.h>

// local includes
#include "newsettings.h"
#include "espnowfunctions.h"

namespace {
wifi_stack::config createConfig();
std::optional<wifi_stack::sta_config> createStaConfig();
wifi_stack::wifi_entry createWifiEntry(const WiFiConfig &wifi_config);
std::optional<wifi_stack::ap_config> createApConfig();
std::optional<uint8_t> ap_channel_override;
bool channelSwitched{false};
} // namespace

void set_ap_channel_override(uint8_t channel)
{
    ap_channel_override = channel;
}

void disable_ap_channel_override()
{
    ap_channel_override = std::nullopt;
}

std::optional<uint8_t>& get_ap_channel_override()
{
    return ap_channel_override;
}

void wifi_begin()
{
    wifi_stack::init(createConfig());
}

void wifi_update()
{
    if (ap_channel_override)
    {
        if (!channelSwitched)
        {
            ESP_LOGI("BOBBY", "switching to channel %d", *ap_channel_override);
            bobby::espnow::send_espnow_message("CHOK");
            channelSwitched = true;
        }
    }
    else
        channelSwitched = false;

    wifi_stack::update(createConfig());
}

esp_err_t wifi_scan()
{
    const auto &sta_config = createStaConfig();
    if (!sta_config)
    {
        ESP_LOGE("BOBBY", "no sta enabled");
        return ESP_FAIL;
    }

    if (const auto result = wifi_stack::begin_scan(*sta_config); !result)
    {
        ESP_LOGE("BOBBY", "begin_scan() failed with %.*s", result.error().size(), result.error().data());
        return ESP_FAIL;
    }

    return ESP_OK;
}

namespace {
wifi_stack::config createConfig()
{
    return wifi_stack::config {
        .base_mac_override = configs.baseMacAddressOverride.value(),
        //.dual_ant = dual_ant_config{},
        .sta = createStaConfig(),
        .ap = createApConfig(),
#ifdef CONFIG_ETH_ENABLED
        .eth = createEthConfig()
#endif
    };
}

std::optional<wifi_stack::sta_config> createStaConfig()
{
    if (!configs.wifiStaEnabled.value())
        return std::nullopt;

    return wifi_stack::sta_config{
        .hostname = configs.hostname.value(),
        .wifis = std::array<wifi_stack::wifi_entry, 10> {
            createWifiEntry(configs.wifi_configs[0]),
            createWifiEntry(configs.wifi_configs[1]),
            createWifiEntry(configs.wifi_configs[2]),
            createWifiEntry(configs.wifi_configs[3]),
            createWifiEntry(configs.wifi_configs[4]),
            createWifiEntry(configs.wifi_configs[5]),
            createWifiEntry(configs.wifi_configs[6]),
            createWifiEntry(configs.wifi_configs[7]),
            createWifiEntry(configs.wifi_configs[8]),
            createWifiEntry(configs.wifi_configs[9])
        },
        .min_rssi = configs.wifiStaMinRssi.value(),
        .long_range = false
    };
}

wifi_stack::wifi_entry createWifiEntry(const WiFiConfig &wifi_config)
{
    std::optional<wifi_stack::static_ip_config> static_ip;
    if (wifi_config.useStaticIp.value())
        static_ip = wifi_stack::static_ip_config {
            .ip = wifi_config.staticIp.value(),
            .subnet = wifi_config.staticSubnet.value(),
            .gateway = wifi_config.staticGateway.value()
        };

    wifi_stack::static_dns_config static_dns;
    if (wifi_config.useStaticDns.value())
    {
        if (wifi_config.staticDns0.value().value())
            static_dns.main = wifi_config.staticDns0.value();
        if (wifi_config.staticDns1.value().value())
            static_dns.backup = wifi_config.staticDns1.value();
        if (wifi_config.staticDns2.value().value())
            static_dns.fallback = wifi_config.staticDns2.value();
    }

    return wifi_stack::wifi_entry {
        .ssid = wifi_config.ssid.value(),
        .key = wifi_config.key.value(),
        .static_ip = static_ip,
        .static_dns = static_dns
    };
}

std::optional<wifi_stack::ap_config> createApConfig()
{
    if (!configs.wifiApEnabled.value())
        return std::nullopt;

//    if (configs.wifiDisableApWhenOnline.value &&
//        cloudStarted &&
//        cloudConnected &&
//        lastCloudConnectedToggled &&
//        espchrono::ago(*lastCloudConnectedToggled) >= 30s)
//        return std::nullopt;

    return wifi_stack::ap_config {
        .hostname = configs.hostname.value(),
        .ssid = configs.wifiApName.value(),
        .key = configs.wifiApKey.value(),
        .static_ip = {
            .ip = configs.wifiApIp.value(),
            .subnet = configs.wifiApMask.value(),
            .gateway = configs.wifiApIp.value(),
        },
        .channel = ap_channel_override ? *ap_channel_override : configs.wifiApChannel.value(),
        .authmode = configs.wifiApAuthmode.value(),
        .ssid_hidden = configs.wifiApHidden.value(),
        .max_connection = 4,
        .beacon_interval = 100,
        .long_range = false
    };
}
} // namespace
