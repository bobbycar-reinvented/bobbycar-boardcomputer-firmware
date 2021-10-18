#pragma once

// Local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "icons/back.h"
#include "icons/settings.h"
#include "texts.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "mainmenu.h"
#include "battery.h"
#include "selectbatterytypemenu.h"
#include "displays/calibratevoltagedisplay.h"

// Helper
class currentBatteryStatus : public virtual TextInterface { public: std::string text() const override { return getBatteryPercentageString(); } };

using namespace espgui;

namespace  {
    class BatteryMenu;
    class CalibrateVoltageDisplay;

    using BatteryCellSeriesChangeScreen = makeComponent<
        ChangeValueDisplay<uint8_t>,
        StaticText<TEXT_CELL_SERIES>,
        BatterySeriesCellsAccessor,
        BackActionInterface<SwitchScreenAction<BatteryMenu>>,
        SwitchScreenAction<BatteryMenu>
    >;

    using BatteryCellParallelChangeScreen = makeComponent<
        ChangeValueDisplay<uint8_t>,
        StaticText<TEXT_CELL_PARALLEL>,
        BatteryParallelCellsAccessor,
        BackActionInterface<SwitchScreenAction<BatteryMenu>>,
        SwitchScreenAction<BatteryMenu>
    >;

    using BatteryWHperKMChangeScreen = makeComponent<
        ChangeValueDisplay<uint16_t>,
        StaticText<TEXT_BATTERY_WHKM>,
        BatteryWHperKMAccessor,
        BackActionInterface<SwitchScreenAction<BatteryMenu>>,
        SwitchScreenAction<BatteryMenu>
    >;
}

namespace  {
    class BatteryMenu :
            public MenuDisplay,
            public StaticText<TEXT_BATTERY>,
            public BackActionInterface<SwitchScreenAction<MainMenu>>
    {
    public:
        BatteryMenu()
        {
            constructMenuItem<makeComponent<MenuItem, currentBatteryStatus,                                                     DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, EmptyText,                                                                DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CELL_SERIES, BatterySeriesCellsAccessor>,        SwitchScreenAction<BatteryCellSeriesChangeScreen>>>();
            constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CELL_PARALLEL, BatteryParallelCellsAccessor>,    SwitchScreenAction<BatteryCellParallelChangeScreen>>>();
            constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BATTERY_WHKM, BatteryWHperKMAccessor>,           SwitchScreenAction<BatteryWHperKMChangeScreen>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECT_CELL_TYPE>,                                        SwitchScreenAction<BatteryTypeMenu>>>();
            constructMenuItem<makeComponent<MenuItem, EmptyText,                                                                DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_CALIBRATE>,                                       SwitchScreenAction<CalibrateVoltageDisplay>, StaticMenuItemIcon<&bobbyicons::settings>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                    SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
