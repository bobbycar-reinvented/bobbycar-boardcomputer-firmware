#include "batterymenu.h"

// 3rdparty lib includes
#include <changevaluedisplay.h>

// local includes
#include "mainmenu.h"
#include "displays/calibratevoltagedisplay.h"
#include "accessors/settingsaccessors.h"

class CurrentBatteryStatusText : public virtual espgui::TextInterface { public: std::string text() const override { return getBatteryPercentageString(); } };

using BatteryCellSeriesChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_CELL_SERIES>,
    BatterySeriesCellsAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BatteryMenu>>,
    espgui::SwitchScreenAction<BatteryMenu>
>;

using BatteryCellParallelChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_CELL_PARALLEL>,
    BatteryParallelCellsAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BatteryMenu>>,
    espgui::SwitchScreenAction<BatteryMenu>
>;

using BatteryWHperKMChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<uint16_t>,
    espgui::StaticText<TEXT_BATTERY_WHKM>,
    BatteryWHperKMAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<BatteryMenu>>,
    espgui::SwitchScreenAction<BatteryMenu>
>;

using namespace espgui;

BatteryMenu::BatteryMenu()
{
    constructMenuItem<makeComponent<MenuItem, CurrentBatteryStatusText,                                                 DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CELL_SERIES, BatterySeriesCellsAccessor>,        SwitchScreenAction<BatteryCellSeriesChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CELL_PARALLEL, BatteryParallelCellsAccessor>,    SwitchScreenAction<BatteryCellParallelChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BATTERY_WHKM, BatteryWHperKMAccessor>,           SwitchScreenAction<BatteryWHperKMChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECT_CELL_TYPE>,                                        SwitchScreenAction<BatteryTypeMenu>>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_CALIBRATE>,                                       SwitchScreenAction<CalibrateVoltageDisplay>, StaticMenuItemIcon<&bobbyicons::settings>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                    SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void BatteryMenu::back()
{
    switchScreen<MainMenu>();
}
