#include "buzzermenu.h"

// 3rdparty lib includes
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "utils.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_BUZZER[] = "Buzzer";
constexpr char TEXT_FRONTFREQ[] = "Front freq";
constexpr char TEXT_FRONTPATTERN[] = "Front pattern";
constexpr char TEXT_BACKFREQ[] = "Back freq";
constexpr char TEXT_BACKPATTERN[] = "Back pattern";
constexpr char TEXT_REVERSEBEEP[] = "Reverse beep";
constexpr char TEXT_REVERSEBEEPFREQ0[] = "Reverse beep freq0";
constexpr char TEXT_REVERSEBEEPFREQ1[] = "Reverse beep freq1";
constexpr char TEXT_REVERSEBEEPDURATION0[] = "Reverse beep duration0";
constexpr char TEXT_REVERSEBEEPDURATION1[] = "Reverse beep duration1";
constexpr char TEXT_BACK[] = "Back";

struct FrontFreqAccessor : public espgui::RefAccessor<uint8_t> { uint8_t &getRef() const override { return controllers.front.command.buzzer.freq; } };
using FrontFreqChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_FRONTFREQ>,
    FrontFreqAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;

struct FrontPatternAccessor : public espgui::RefAccessor<uint8_t> { uint8_t &getRef() const override { return controllers.front.command.buzzer.pattern; } };
using FrontPatternChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_FRONTPATTERN>,
    FrontPatternAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;

struct BackFreqAccessor : public espgui::RefAccessor<uint8_t> { uint8_t &getRef() const override { return controllers.back.command.buzzer.freq; } };
using BackFreqChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_BACKFREQ>,
    BackFreqAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;

struct BackPatternAccessor : public espgui::RefAccessor<uint8_t> { uint8_t &getRef() const override { return controllers.back.command.buzzer.pattern; } };
using BackPatternChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_BACKPATTERN>,
    BackPatternAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;

using ReverseBeepFreq0ChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_REVERSEBEEPFREQ0>,
    ReverseBeepFreq0Accessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;
using ReverseBeepFreq1ChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_REVERSEBEEPFREQ1>,
    ReverseBeepFreq1Accessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;
using ReverseBeepDuration0ChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_REVERSEBEEPDURATION0>,
    ReverseBeepDuration0Accessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;
using ReverseBeepDuration1ChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_REVERSEBEEPDURATION1>,
    ReverseBeepDuration1Accessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BuzzerMenu>>
>;
} // namespace

using namespace espgui;

BuzzerMenu::BuzzerMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTFREQ>,            SwitchScreenAction<FrontFreqChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTPATTERN>,         SwitchScreenAction<FrontPatternChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKFREQ>,             SwitchScreenAction<BackFreqChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKPATTERN>,          SwitchScreenAction<BackPatternChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEP>,          BobbyCheckbox, ReverseBeepAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPFREQ0>,     SwitchScreenAction<ReverseBeepFreq0ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPFREQ1>,     SwitchScreenAction<ReverseBeepFreq1ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPDURATION0>, SwitchScreenAction<ReverseBeepDuration0ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REVERSEBEEPDURATION1>, SwitchScreenAction<ReverseBeepDuration1ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string BuzzerMenu::text() const
{
    return TEXT_BUZZER;
}

void BuzzerMenu::back()
{
    switchScreen<SettingsMenu>();
}
