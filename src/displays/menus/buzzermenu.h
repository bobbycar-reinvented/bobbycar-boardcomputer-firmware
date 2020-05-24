#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "settingsaccessors.h"

namespace {
class BuzzerMenu;
class SettingsMenu;
}

namespace {
struct FrontFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.freq; } };
using FrontFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_FRONTFREQ>, FrontFreqAccessor, SwitchScreenAction<BuzzerMenu>>;

struct FrontPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return front.command.buzzer.pattern; } };
using FrontPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_FRONTPATTERN>, FrontPatternAccessor, SwitchScreenAction<BuzzerMenu>>;

struct BackFreqAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.freq; } };
using BackFreqChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_BACKFREQ>, BackFreqAccessor, SwitchScreenAction<BuzzerMenu>>;

struct BackPatternAccessor : public RefAccessor<uint8_t> { uint8_t &getRef() const override { return back.command.buzzer.pattern; } };
using BackPatternChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_BACKPATTERN>, BackPatternAccessor, SwitchScreenAction<BuzzerMenu>>;

using ReverseBeepFreq0ChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_REVERSEBEEPFREQ0>, ReverseBeepFreq0Accessor, SwitchScreenAction<BuzzerMenu>>;
using ReverseBeepFreq1ChangeScreen = makeComponent<ChangeValueDisplay<uint8_t>, StaticText<TEXT_REVERSEBEEPFREQ1>, ReverseBeepFreq1Accessor, SwitchScreenAction<BuzzerMenu>>;
using ReverseBeepDuration0ChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_REVERSEBEEPDURATION0>, ReverseBeepDuration0Accessor, SwitchScreenAction<BuzzerMenu>>;
using ReverseBeepDuration1ChangeScreen = makeComponent<ChangeValueDisplay<int16_t>, StaticText<TEXT_REVERSEBEEPDURATION1>, ReverseBeepDuration1Accessor, SwitchScreenAction<BuzzerMenu>>;

class BuzzerMenu :
    public MenuDisplay,
    public StaticText<TEXT_BUZZER>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_FRONTFREQ>,            SwitchScreenAction<FrontFreqChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_FRONTPATTERN>,         SwitchScreenAction<FrontPatternChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACKFREQ>,             SwitchScreenAction<BackFreqChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACKPATTERN>,          SwitchScreenAction<BackPatternChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEP>,          ToggleBoolAction, CheckboxIcon, ReverseBeepAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPFREQ0>,     SwitchScreenAction<ReverseBeepFreq0ChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPFREQ1>,     SwitchScreenAction<ReverseBeepFreq1ChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPDURATION0>, SwitchScreenAction<ReverseBeepDuration0ChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPDURATION1>, SwitchScreenAction<ReverseBeepDuration1ChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
