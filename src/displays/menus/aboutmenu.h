#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "esptexthelpers.h"
#include "texts.h"

// forward declares
namespace {
class SettingsMenu;
} // namespace

namespace {
constexpr char TEXT_VERSION[] = "Version: 1.0";
constexpr char TEXT_ESPINFO[] = "ESP info:";

class AboutMenu :
    public MenuDisplay,
    public StaticText<TEXT_ABOUT>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    AboutMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_VERSION>,                                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                                        DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ESPINFO>,                                   DummyAction>>();
        constructItem<makeComponent<MenuItem, EspHeapSizeText,              StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFreeHeapText,              StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspMinFreeHeapText,           StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspMaxAllocHeapText,          StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspPsramSizeText,             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFreePsramText,             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspMinFreePsramText,          StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspMaxAllocPsramText,         StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspChipRevisionText,          StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspCpuFreqMHzText,            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspCycleCountText,            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspSdkVersionText,            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFlashChipSizeText,         StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFlashChipSpeedText,        StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFlashChipModeText,         StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspSketchSizeText,            StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspSketchMd5Text,             StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, EspFreeSketchSpaceText,       StaticFont<2>, DisabledColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,        SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
