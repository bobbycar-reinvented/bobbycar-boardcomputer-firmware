#pragma once

#include "sdkconfig.h"

// system includes
#include <string>

// 3rdparty lib includes
#include <accessorinterface.h>
#include <espwifiutils.h>

// local includes
#include "newsettings.h"
#include "accessorhelpers.h"

struct WifiStaEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.wifiStaEnabled; } };

class WifiStaConfigSsidAccessor : public virtual NewSettingsAccessor<std::string>
{
public:
    WifiStaConfigSsidAccessor(int index) : m_index{index} {}
    ConfigWrapper<std::string>& getConfig() const override { return configs.wifi_configs[m_index].ssid; }
private:
    const int m_index;
};

class WifiStaConfigKeyAccessor : public virtual NewSettingsAccessor<std::string>
{
public:
    WifiStaConfigKeyAccessor(int index) : m_index{index} {}
    ConfigWrapper<std::string>& getConfig() const override { return configs.wifi_configs[m_index].key; }
private:
    const int m_index;
};

class WifiStaConfigUseStaticIpAccessor : public virtual NewSettingsAccessor<bool>
{
public:
    WifiStaConfigUseStaticIpAccessor(int index) : m_index{index} {}
    ConfigWrapper<bool>& getConfig() const override { return configs.wifi_configs[m_index].useStaticIp; }
private:
    const int m_index;
};

class WifiStaConfigStaticIpAccessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticIpAccessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticIp; }
private:
    const int m_index;
};

class WifiStaConfigStaticSubnetAccessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticSubnetAccessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticSubnet; }
private:
    const int m_index;
};

class WifiStaConfigStaticGatewayAccessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticGatewayAccessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticGateway; }
private:
    const int m_index;
};

class WifiStaConfigUseStaticDnsAccessor : public virtual NewSettingsAccessor<bool>
{
public:
    WifiStaConfigUseStaticDnsAccessor(int index) : m_index{index} {}
    ConfigWrapper<bool>& getConfig() const override { return configs.wifi_configs[m_index].useStaticDns; }
private:
    const int m_index;
};

class WifiStaConfigStaticDns0Accessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns0Accessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticDns0; }
private:
    const int m_index;
};

class WifiStaConfigStaticDns1Accessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns1Accessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticDns1; }
private:
    const int m_index;
};

class WifiStaConfigStaticDns2Accessor : public virtual NewSettingsAccessor<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns2Accessor(int index) : m_index{index} {}
    ConfigWrapper<wifi_stack::ip_address_t>& getConfig() const override { return configs.wifi_configs[m_index].staticDns2; }
private:
    const int m_index;
};
