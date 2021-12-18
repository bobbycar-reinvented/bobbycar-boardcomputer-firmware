#include "qraction.h"

#include <actioninterface.h>
#include <string>
#include <screenmanager.h>
#include "displays/qrdisplay.h"

using namespace espgui;

SwitchQrDisplayAction::SwitchQrDisplayAction(qraction::QrMenu qrmenu) : m_msg{qrmenu.message}, m_ver{qrmenu.ver} {}

void SwitchQrDisplayAction::triggered()
{
    switchScreen<QrDisplay>(m_msg, m_ver);
}
