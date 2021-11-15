#include "statisticsmenu.h"

// local includes
#include "mainmenu.h"
#include "actions/dummyaction.h"
#include "actioninterface.h"
#include "fmt/core.h"
#include "utils.h"

using namespace espgui;

class WhPerKmText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        float avgVoltage = 0;
        for (auto &controller : controllers)
        {
            avgVoltage += controller.getCalibratedVoltage();
        }
        avgVoltage = avgVoltage / controllers.size();

        auto watt = sumCurrent * avgVoltage;
        auto w_per_kmh = watt / avgSpeedKmh;
        return fmt::format("{:.0f} Wh/km", w_per_kmh);
    }
};

class UptimeText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return get_current_uptime_string();
    }
};

class CurrentKilometersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("curr: {:.2f}m", drivingStatistics.meters_driven);
    }
};

class TotalKilometersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("total: {:.2f}m", drivingStatistics.totalMeters );
    }
};

class CurrentDrivingTimeText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return get_current_driving_time_string();
    }
};

class SavedTotalCentimetersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("saved: {}cm", settings.savedStatistics.totalCentimeters );
    }
};

class SaveKilometersAction : public virtual ActionInterface {
public:
    void triggered() override {
        drivingStatistics.last_cm_written = drivingStatistics.totalMeters * 100;
        settings.savedStatistics.totalCentimeters = drivingStatistics.last_cm_written;
        saveSettings();
    }
};

class ClearCurrentStatsAction : public virtual ActionInterface {
public:
    void triggered() override {
        drivingStatistics.meters_driven = 0.;
        drivingStatistics.currentDrivingTime = 0;
    }
};

StatisticsMenu::StatisticsMenu()
{
    constructMenuItem<makeComponent<MenuItem, WhPerKmText,                                      DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, UptimeText,                                       DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentKilometersText,                            DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentDrivingTimeText,                           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TotalKilometersText,                              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, SavedTotalCentimetersText,                        DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSSAVE>,                       SaveKilometersAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSCLEAR>,                      ClearCurrentStatsAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                            SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void StatisticsMenu::back()
{
    switchScreen<MainMenu>();
}
