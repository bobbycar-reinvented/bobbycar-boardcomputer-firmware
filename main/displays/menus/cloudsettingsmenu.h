#pragma once

// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "cloudtexthelpers.h"
#include "accessors/settingsaccessors.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class CloudSettingsMenu;
class SettingsMenu;
} // namespace

namespace {
using CloudTransmitTimeoutChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CLOUDTRANSMITTIMEOUT>,
    CloudTransmitTimeoutAccessor,
    BackActionInterface<SwitchScreenAction<CloudSettingsMenu>>,
    SwitchScreenAction<CloudSettingsMenu>
>;
} // namespace

namespace {
#ifdef FEATURE_CLOUD
class CloudSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_CLOUDSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    CloudSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDENABLED>,         ToggleBoolAction, CheckboxIcon, CloudEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDTRANSMITTIMEOUT>, SwitchScreenAction<CloudTransmitTimeoutChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, CloudCreatedText,                      DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, CloudStartedText,                      DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, CloudConnectedText,                    DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
#endif
} // namespace
