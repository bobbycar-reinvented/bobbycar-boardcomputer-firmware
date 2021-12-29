#pragma once

// 3rdparty lib includes
#include <textinterface.h>

class WifiApNameText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApKeyText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApMacText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApIpText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApMaskText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApHostnameText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

class WifiApClientsText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};
