#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <actioninterface.h>

// local includes
#include "actions/qraction.h"
#include "displays/qrdisplay.h"
#include "displays/qrimportdisplay.h"

namespace qraction {
struct QrMenu {
    std::string message;
    std::string text;
};
} // namespace

template<typename TMenu>
class SwitchQrDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit SwitchQrDisplayAction(const qraction::QrMenu &qrmenu) : m_msg{qrmenu.message} {}
    explicit SwitchQrDisplayAction(qraction::QrMenu &&qrmenu) : m_msg{std::move(qrmenu.message)} {}

    void triggered() override
    {
        espgui::pushScreen<QrDisplay<TMenu>>(m_msg);
    }
private:
    std::string m_msg;
};

template<typename TMenu>
class SwitchQrImportDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit SwitchQrImportDisplayAction(const std::string &nvskey) : m_nvskey{nvskey} {}
    explicit SwitchQrImportDisplayAction(std::string &&nvskey) : m_nvskey{std::move(nvskey)} {}

    void triggered() override
    {
        espgui::pushScreen<QrImportDisplay<TMenu>>(std::move(m_nvskey));
    }
private:
    std::string m_nvskey;
};
