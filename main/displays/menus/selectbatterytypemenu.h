#pragma once

// Local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "icons/back.h"
#include "texts.h"
#include "actions/switchscreenaction.h"
#include "batterymenu.h"
#include "battery.h"
#include "actioninterface.h"

// Helper
class currentBatteryType : public virtual TextInterface { public: std::string text() const override { return getBatteryCellTypeString(); } };

using namespace espgui;

namespace  {
    class BatteryTypeMenu;
    class BatteryMenu;

    template<BatteryCellType T>
    class BatterySelectTypeAction : public virtual ActionInterface
    {
    public:
        void triggered() override { settings.battery.cellType = uint8_t(T); saveSettings(); }
    };
} // namespace

namespace  {
    class BatteryTypeMenu :
            public MenuDisplay,
            public StaticText<TEXT_SELECT_CELL_TYPE>,
            public BackActionInterface<SwitchScreenAction<BatteryMenu>>
    {
    public:
        BatteryTypeMenu()
        {
            constructMenuItem<makeComponent<MenuItem, currentBatteryType,                            DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_22P>,             BatterySelectTypeAction<BatteryCellType::_22P>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_HG2>,             BatterySelectTypeAction<BatteryCellType::HG2>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_MH1>,             BatterySelectTypeAction<BatteryCellType::MH1>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_VTC5>,            BatterySelectTypeAction<BatteryCellType::VTC5>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_BAK_25R>,         BatterySelectTypeAction<BatteryCellType::BAK_25R>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
