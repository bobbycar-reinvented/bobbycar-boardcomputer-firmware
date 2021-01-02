#pragma once

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#ifdef FEATURE_BLUETOOTH
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothflushaction.h"
#include "actions/bluetoothendaction.h"
#include "actions/bluetoothdisconnectaction.h"
#endif
#include "actions/switchscreenaction.h"
#include "bluetoothtexthelpers.h"
#include "settingsaccessors.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class SettingsMenu;
} // namespace

namespace {
#ifdef FEATURE_BLUETOOTH
class BluetoothSettingsMenu;

using AutoBluetoothModeChangeDisplay = makeComponent<
    ChangeValueDisplay<BluetoothMode>,
    StaticText<TEXT_AUTOBLUETOOTHMODE>,
    AutoBluetoothModeAccessor,
    BackActionInterface<SwitchScreenAction<BluetoothSettingsMenu>>,
    SwitchScreenAction<BluetoothSettingsMenu>
>;

class BluetoothSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BLUETOOTHSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    BluetoothSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, BluetoothAvailableText,                 DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, BluetoothHasClientText,                 DisabledColor, DummyAction>>();
//        constructItem<makeComponent<MenuItem, BluetoothConnectedText,                 DisabledColor, DummyAction>>(); // crashes
        constructItem<makeComponent<MenuItem, BluetoothIsReadyText,                   DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, BluetoothIsReadyMasterText,             DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        BluetoothBeginAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  BluetoothBeginMasterAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        BluetoothFlushAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          BluetoothEndAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   BluetoothDisconnectAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_AUTOBLUETOOTHMODE>,     SwitchScreenAction<AutoBluetoothModeChangeDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
#endif
} // namespace
