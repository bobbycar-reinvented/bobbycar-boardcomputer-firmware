#include "batterydebugmenu.h"

// local includes
#include "debugmenu.h"
#include "accessors/settingsaccessors.h"
#include "fmt/core.h"

class CurrentBatteryStatusText : public virtual espgui::TextInterface { public: std::string text() const override { return getBatteryPercentageString(); } };
class CurrentAdvancedBatteryPercentageText : public virtual espgui::TextInterface { public: std::string text() const override { return getBatteryAdvancedPercentageString(); } };

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
        return fmt::format("{:.0f} {:.0f}W/kmh", avgSpeedKmh, w_per_kmh);
    }
};
class BatteryDebug3Text : public virtual espgui::TextInterface { public: std::string text() const override { return fmt::format("{}fA {}bA", fixCurrent(controllers.front.feedback.left.dcLink + controllers.front.feedback.right.dcLink), fixCurrent(controllers.back.feedback.left.dcLink + controllers.back.feedback.right.dcLink)); } };

using namespace espgui;

BatteryDebugMenu::BatteryDebugMenu()
{
    constructMenuItem<makeComponent<MenuItem, CurrentBatteryStatusText,                                                 DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryDebugText,                                                         DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryDebug2Text,                                                        DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryDebug3Text,                                                        DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentAdvancedBatteryPercentageText,                                     DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                    SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void BatteryDebugMenu::back()
{
    switchScreen<DebugMenu>();
}
