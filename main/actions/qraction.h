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

class PushQrDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit PushQrDisplayAction(const qraction::QrMenu &qrmenu) : m_msg{qrmenu.message} {}
    explicit PushQrDisplayAction(qraction::QrMenu &&qrmenu) : m_msg{std::move(qrmenu.message)} {}

    void triggered() override
    {
        espgui::pushScreen<QrDisplay>(m_msg);
    }
private:
    std::string m_msg;
};

template<typename TMenu>
class PushQrImportDisplayAction : public virtual espgui::ActionInterface
{
public:
    explicit PushQrImportDisplayAction(const std::string &nvskey) : m_nvskey{nvskey} {}
    explicit PushQrImportDisplayAction(std::string &&nvskey) : m_nvskey{std::move(nvskey)} {}

    void triggered() override
    {
        espgui::pushScreen<QrImportDisplay<TMenu>>(std::move(m_nvskey));
    }
private:
    std::string m_nvskey;
};
