#pragma once

#include <actioninterface.h>
#include <string>

#include "actions/qraction.h"

namespace qraction {
struct QrMenu {
    std::string_view message;
    uint8_t ver;
};
} // namespace

class SwitchQrDisplayAction : public virtual espgui::ActionInterface
{
public:
    SwitchQrDisplayAction(qraction::QrMenu qrmenu);

    void triggered() override;
private:
    std::string_view m_msg;
    uint8_t m_ver;
};
