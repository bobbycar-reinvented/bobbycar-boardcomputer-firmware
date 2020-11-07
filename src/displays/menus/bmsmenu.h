#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
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

namespace {
class MainMenu;
}

namespace {
#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
class BmsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BMS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_CONNECTBMS>,       BluetoothConnectBmsAction>,
        makeComponent<MenuItem, StaticText<TEXT_DISCONNECTBMS>,    BluetoothDisconnectAction>,
        makeComponent<MenuItem, BluetoothHasClientText,            DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_TURNONCHARGE>,     BmsTurnOnChargeAction>,
        makeComponent<MenuItem, StaticText<TEXT_TURNOFFCHARGE>,    BmsTurnOffChargeAction>,
        makeComponent<MenuItem, StaticText<TEXT_TURNONDISCHARGE>,  BmsTurnOnDischargeAction>,
        makeComponent<MenuItem, StaticText<TEXT_TURNOFFDISCHARGE>, BmsTurnOffDischargeAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
#endif
}
