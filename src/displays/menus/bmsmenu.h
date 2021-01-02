#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
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

//forward declares
namespace {
class MainMenu;
} // namespace

namespace {
#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
class BmsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BMS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public ContainerMenuDefinition
{
public:
    BmsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_CONNECTBMS>,       BluetoothConnectBmsAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DISCONNECTBMS>,    BluetoothDisconnectAction>>();
        constructItem<makeComponent<MenuItem, BluetoothHasClientText,            DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TURNONCHARGE>,     BmsTurnOnChargeAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFCHARGE>,    BmsTurnOffChargeAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TURNONDISCHARGE>,  BmsTurnOnDischargeAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFDISCHARGE>, BmsTurnOffDischargeAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
#endif
} // namespace
