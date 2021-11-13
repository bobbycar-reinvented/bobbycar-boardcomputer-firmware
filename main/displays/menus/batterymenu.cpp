#include "batterymenu.h"

// 3rdparty lib includes
#include <changevaluedisplay.h>

// local includes
#include "mainmenu.h"
#include "displays/calibratevoltagedisplay.h"
#include "accessors/settingsaccessors.h"
#include "fmt/core.h"

class CurrentBatteryStatusText : public virtual espgui::TextInterface { public: std::string text() const override { return getBatteryPercentageString(); } };
class BatteryDebugText : public virtual espgui::TextInterface { public: std::string text() const override { return getBatteryDebugString(); } };
class BatteryDebug2Text : public virtual espgui::TextInterface {
    public: std::string text() const override {
        float avgVoltage = 0;
        for (auto &controller : controllers)
        {
            avgVoltage += controller.getCalibratedVoltage();
        }
        avgVoltage = avgVoltage / controllers.size();

        auto watt = sumCurrent * avgVoltage;
        auto w_per_kmh = watt / avgSpeedKmh;
        return fmt::format("{:.1f} {:.2f}W/kmh", avgSpeedKmh, w_per_kmh);
    }
};

class BatteryDebug3Text : public virtual espgui::TextInterface { public: std::string text() const override { return fmt::format("{}fA {}bA", fixCurrent(controllers.front.feedback.left.dcLink + controllers.front.feedback.right.dcLink), fixCurrent(controllers.back.feedback.left.dcLink + controllers.back.feedback.right.dcLink)); } };

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
    constructMenuItem<makeComponent<MenuItem, BatteryDebugText,                                                         DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryDebug2Text,                                                        DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryDebug3Text,                                                        DisabledColor, DummyAction>>();
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
