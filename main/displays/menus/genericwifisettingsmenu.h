#pragma once

// local includes
#include "menudisplay.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "wifitexthelpers.h"
#include "accessors/wifiaccessors.h"
#include "texts.h"

// forward declares
namespace {
class GenericWifiSettingsMenu;
class WifiSettingsMenu;
} // namespace

using namespace espgui;

namespace {
class GenericWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_GENERICWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>
{
public:
    GenericWifiSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
