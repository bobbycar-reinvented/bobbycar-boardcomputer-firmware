#pragma once

// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"
#ifdef FEATURE_LEDSTRIP
#include "ledstrip.h"
#endif

// forward declares
namespace {
class MainWindow;
} // namespace

using namespace espgui;

namespace {
#ifdef FEATURE_LEDSTRIP
struct EnableLedAnimationAccessor : public RefAccessor<bool> { bool &getRef() const override { return enableLedAnimation; } };

class LedstripMenu :
    public MenuDisplay,
    public StaticText<TEXT_LEDSTRIP>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    LedstripMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LEDANIMATION>, ToggleBoolAction, CheckboxIcon, EnableLedAnimationAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BRAKELIGHTS>,  ToggleBoolAction, CheckboxIcon, EnableBrakeLightsAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
#endif
} // namespace
