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

    class BatterySelectType22PAction : public virtual ActionInterface
    {
    public:
        void triggered() override { settings.battery.cellType = BATTERY_CELLTYPE_22P; saveSettings(); }
    };

    class BatterySelectTypeHG2Action : public virtual ActionInterface
    {
    public:
        void triggered() override { settings.battery.cellType = BATTERY_CELLTYPE_HG2; saveSettings(); }
    };

    class BatterySelectTypeMH1Action : public virtual ActionInterface
    {
    public:
        void triggered() override { settings.battery.cellType = BATTERY_CELLTYPE_MH1; saveSettings(); }
    };

    class BatterySelectTypeVTC5Action : public virtual ActionInterface
    {
    public:
        void triggered() override { settings.battery.cellType = BATTERY_CELLTYPE_VTC5; saveSettings(); }
    };
}

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
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_22P>,             BatterySelectType22PAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_HG2>,             BatterySelectTypeHG2Action>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_MH1>,             BatterySelectTypeMH1Action>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_TYPE_VTC5>,            BatterySelectTypeVTC5Action>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
