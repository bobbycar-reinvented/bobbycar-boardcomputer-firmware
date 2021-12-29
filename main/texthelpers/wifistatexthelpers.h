#pragma once

// 3rdparty lib includes
#include <textinterface.h>

class WifiStaStatusText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaMacText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaScanStatusText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiSsidText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiBssidText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiRssiText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiAuthmodeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiPairwiseCipherText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiGroupCipherText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaIpText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaNetmaskText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaGatewayText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaHostnameText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaIpv6LinklocalText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiStaIpv6GlobalText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};
