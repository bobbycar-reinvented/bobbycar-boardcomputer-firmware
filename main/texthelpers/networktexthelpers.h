#pragma once

// 3rdparty lib includes
#include <textinterface.h>

class WifiDefaultMacText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiBaseMacText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class DnsText : public virtual espgui::TextInterface
{
public:
    DnsText(uint8_t index) : m_index{index} {}

    std::string text() const override;

private:
    const uint8_t m_index;
};

class WifiTxPowerText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};
