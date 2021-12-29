#pragma once

// 3rdparty lib includes
#include <textinterface.h>

class WifiApMacText : public virtual espgui::TextInterface
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
