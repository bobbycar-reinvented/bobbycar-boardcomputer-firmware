#pragma once

#include "sdkconfig.h"

// system includes
#include <string>

// 3rdparty lib includes
#include <accessorinterface.h>
#include <espwifiutils.h>

class WifiStaEnabledAccessor : public virtual espgui::AccessorInterface<bool>
{
public:
    bool getValue() const override;
    void setValue(bool value) override;
};

class WifiStaConfigSsidAccessor : public virtual espgui::AccessorInterface<std::string>
{
public:
    WifiStaConfigSsidAccessor(int index) : m_index{index} {}

    std::string getValue() const override;
    void setValue(std::string value) override;

private:
    const int m_index;
};

class WifiStaConfigKeyAccessor : public virtual espgui::AccessorInterface<std::string>
{
public:
    WifiStaConfigKeyAccessor(int index) : m_index{index} {}

    std::string getValue() const override;
    void setValue(std::string value) override;

private:
    const int m_index;
};

class WifiStaConfigUseStaticIpAccessor : public virtual espgui::AccessorInterface<bool>
{
public:
    WifiStaConfigUseStaticIpAccessor(int index) : m_index{index} {}

    bool getValue() const override;
    void setValue(bool value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticIpAccessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticIpAccessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticSubnetAccessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticSubnetAccessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticGatewayAccessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticGatewayAccessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};

class WifiStaConfigUseStaticDnsAccessor : public virtual espgui::AccessorInterface<bool>
{
public:
    WifiStaConfigUseStaticDnsAccessor(int index) : m_index{index} {}

    bool getValue() const override;
    void setValue(bool value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns0Accessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns0Accessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns1Accessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns1Accessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns2Accessor : public virtual espgui::AccessorInterface<wifi_stack::ip_address_t>
{
public:
    WifiStaConfigStaticDns2Accessor(int index) : m_index{index} {}

    wifi_stack::ip_address_t getValue() const override;
    void setValue(wifi_stack::ip_address_t value) override;

private:
    const int m_index;
};
