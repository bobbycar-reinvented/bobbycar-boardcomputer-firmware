#include "setupquickactionsmenu.h"

// 3rdparty lib includes
#include <textwithvaluehelper.h>

// local includes
#include "actions/switchscreenaction.h"
#include "accessors/settingsaccessors.h"
#include "displays/bobbychangevaluedisplay.h"
#include "changevaluedisplay_bobbyquickactions.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"
#include "icons/back.h"
#include "bobbyquickactions.h"

using namespace espgui;

namespace {
constexpr char TEXT_SETUPQUICKACTIONS[] = "Setup QuickActions";
constexpr char TEXT_SETUPLEFT2[] = "&sSetup Left2";
constexpr char TEXT_SETUPRIGHT2[] = "&sSetup Right2";
constexpr char TEXT_SETUPUP2[] = "&sSetup Up2";
constexpr char TEXT_SETUPDOWN2[] = "&sSetup Down2";
constexpr char TEXT_SETUPEXTRA1[] = "&sSetup Extra1";
constexpr char TEXT_SETUPEXTRA2[] = "&sSetup Extra2";
constexpr char TEXT_SETUPEXTRA3[] = "&sSetup Extra3";
constexpr char TEXT_SETUPEXTRA4[] = "&sSetup Extra4";
constexpr char TEXT_BACK[] = "Back";

template<typename Tvalue, const char* TEXT, typename Accessor, typename Screen>
using QuickActionChangeValueDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<Tvalue>,
    espgui::StaticText<TEXT>,
    Accessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<Screen>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<Screen>>
>;
} // namespace

SetupQuickActionsMenu::SetupQuickActionsMenu()
{
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPLEFT2, QuickActionLeft2Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPLEFT2, QuickActionLeft2Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPRIGHT2, QuickActionRight2Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPRIGHT2, QuickActionRight2Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPUP2, QuickActionUp2Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPUP2, QuickActionUp2Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPDOWN2, QuickActionDown2Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPDOWN2, QuickActionDown2Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPEXTRA1, QuickActionExtra1Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPEXTRA1, QuickActionExtra1Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPEXTRA2, QuickActionExtra2Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPEXTRA2, QuickActionExtra2Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPEXTRA3, QuickActionExtra3Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPEXTRA3, QuickActionExtra3Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SETUPEXTRA4, QuickActionExtra4Accessor>,    SwitchScreenAction<QuickActionChangeValueDisplay<BobbyQuickActions, TEXT_SETUPEXTRA4, QuickActionExtra4Accessor, SetupQuickActionsMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,     SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string SetupQuickActionsMenu::text() const
{
    return TEXT_SETUPQUICKACTIONS;
}

void SetupQuickActionsMenu::back()
{
    switchScreen<BoardcomputerHardwareSettingsMenu>();
}
