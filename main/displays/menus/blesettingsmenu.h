#pragma once

// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "bletexthelpers.h"
#include "accessors/settingsaccessors.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class SettingsMenu;
} // namespace

using namespace espgui;

namespace {
#ifdef FEATURE_BLE
class BleSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BLESETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    BleSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLEENABLED>, ToggleBoolAction, CheckboxIcon, BleEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, BleServerPeerDevicesText,    DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, BleCharacSubscribedText,     DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
#endif
} // namespace
