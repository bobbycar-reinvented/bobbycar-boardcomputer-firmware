#include "qraction.h"

#include <actioninterface.h>
#include <string>
#include <screenmanager.h>
#include "displays/qrdisplay.h"
#include "displays/qrimportdisplay.h"

using namespace espgui;

SwitchQrDisplayAction::SwitchQrDisplayAction(const qraction::QrMenu &qrmenu) :
    m_msg{qrmenu.message}
{
}

SwitchQrDisplayAction::SwitchQrDisplayAction(qraction::QrMenu &&qrmenu) :
    m_msg{std::move(qrmenu.message)}
{
}

void SwitchQrDisplayAction::triggered()
{
    switchScreen<QrDisplay>(m_msg);
}

SwitchQrImportDisplayAction::SwitchQrImportDisplayAction(const std::string &nvskey) :
    m_nvskey{nvskey}
{
}

SwitchQrImportDisplayAction::SwitchQrImportDisplayAction(std::string &&nvskey) :
    m_nvskey{std::move(nvskey)}
{
}

void SwitchQrImportDisplayAction::triggered()
{
    switchScreen<QrImportDisplay>(std::move(m_nvskey));
}
