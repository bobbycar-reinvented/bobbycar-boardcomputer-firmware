#pragma once

// 3rdparty lib includes
#include <textinterface.h>

class WifiStaConfigSsidText : public virtual espgui::TextInterface
{
public:
    WifiStaConfigSsidText(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigKeyText : public virtual espgui::TextInterface
{
public:
    WifiStaConfigKeyText(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticIpText : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticIpText(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticSubnetText : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticSubnetText(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticGatewayText : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticGatewayText(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns0Text : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticDns0Text(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns1Text : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticDns1Text(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};

class WifiStaConfigStaticDns2Text : public virtual espgui::TextInterface
{
public:
    WifiStaConfigStaticDns2Text(int index) : m_index{index} {}

    std::string text() const override;

private:
    const int m_index;
};
