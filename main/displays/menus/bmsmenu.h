#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#ifdef FEATURE_BLUETOOTH
#include "actions/bluetoothconnectbmsaction.h"
#include "actions/bluetoothdisconnectaction.h"
#endif
#include "actions/dummyaction.h"
#include "actions/bmsturnonchargeaction.h"
#include "actions/bmsturnoffchargeaction.h"
#include "actions/bmsturnondischargeaction.h"
#include "actions/bmsturnoffdischargeaction.h"
#include "actions/switchscreenaction.h"
#include "bluetoothtexthelpers.h"
#include "icons/back.h"
#include "texts.h"

using namespace espgui;

namespace {
#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
class BmsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BMS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    BmsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CONNECTBMS>,       BluetoothConnectBmsAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISCONNECTBMS>,    BluetoothDisconnectAction>>();
        constructMenuItem<makeComponent<MenuItem, BluetoothHasClientText,            DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNONCHARGE>,     BmsTurnOnChargeAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFCHARGE>,    BmsTurnOffChargeAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNONDISCHARGE>,  BmsTurnOnDischargeAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFDISCHARGE>, BmsTurnOffDischargeAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
#endif
} // namespace
