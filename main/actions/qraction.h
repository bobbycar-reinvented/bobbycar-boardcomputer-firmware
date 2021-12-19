#pragma once

#include <actioninterface.h>
#include <string>

#include "actions/qraction.h"

namespace qraction {
struct QrMenu {
    std::string message;
    std::string text;
    uint8_t ver;
};
} // namespace

class SwitchQrDisplayAction : public virtual espgui::ActionInterface
{
public:
    SwitchQrDisplayAction(qraction::QrMenu qrmenu);

    void triggered() override;
private:
    std::string m_msg;
    uint8_t m_ver;
};

class SwitchQrImportDisplayAction : public virtual espgui::ActionInterface
{
public:
    SwitchQrImportDisplayAction(std::string nvskey);

    void triggered() override;
private:
    std::string m_nvskey;
};
