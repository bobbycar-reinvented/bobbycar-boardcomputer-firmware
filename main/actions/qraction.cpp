#include "qraction.h"

#include <actioninterface.h>
#include <string>
#include <screenmanager.h>
#include "displays/qrdisplay.h"
#include "displays/qrimportdisplay.h"

using namespace espgui;

SwitchQrDisplayAction::SwitchQrDisplayAction(qraction::QrMenu qrmenu) : m_msg{qrmenu.message}, m_ver{qrmenu.ver} {}

void SwitchQrDisplayAction::triggered()
{
    switchScreen<QrDisplay>(m_msg, m_ver);
}

SwitchQrImportDisplayAction::SwitchQrImportDisplayAction(std::string nvskey) : m_nvskey{nvskey} {}

void SwitchQrImportDisplayAction::triggered()
{
    switchScreen<QrImportDisplay>(m_nvskey);
}
