#pragma once

// local includes
#include "accessorhelpers.h"
#include "newsettings.h"

struct WifiApEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.wifiApEnabled; } };
//struct WifiApDisableWhenOnlineAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.wifiDisableApWhenOnline; } };
struct WifiApNameAccessor : public NewSettingsAccessor<std::string> { ConfigWrapper<std::string> &getConfig() const override { return configs.wifiApName; } };
struct WifiApKeyAccessor : public NewSettingsAccessor<std::string> { ConfigWrapper<std::string> &getConfig() const override { return configs.wifiApKey; } };
struct WifiApIpAccessor : public NewSettingsAccessor<wifi_stack::ip_address_t> { ConfigWrapper<wifi_stack::ip_address_t> &getConfig() const override { return configs.wifiApIp; } };
struct WifiApMaskAccessor : public NewSettingsAccessor<wifi_stack::ip_address_t> { ConfigWrapper<wifi_stack::ip_address_t> &getConfig() const override { return configs.wifiApMask; } };
struct WifiApChannelAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.wifiApChannel; } };
struct WifiApAuthmodeAccessor : public NewSettingsAccessor<wifi_auth_mode_t> { ConfigWrapper<wifi_auth_mode_t> &getConfig() const override { return configs.wifiApAuthmode; } };
