#pragma once

#include <actioninterface.h>
#include <string>

#include "actions/qraction.h"

namespace qraction {
struct QrMenu {
    std::string message;
    std::string text;
};
} // namespace

class SwitchQrDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit SwitchQrDisplayAction(const qraction::QrMenu &qrmenu);
    explicit SwitchQrDisplayAction(qraction::QrMenu &&qrmenu);

    void triggered() override;
private:
    std::string m_msg;
};

class SwitchQrImportDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit SwitchQrImportDisplayAction(const std::string &nvskey);
    explicit SwitchQrImportDisplayAction(std::string &&nvskey);

    void triggered() override;
private:
    std::string m_nvskey;
};
