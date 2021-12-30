#include "calibratevoltagedisplay.h"

// 3rdparty lib includes
#include <menuitem.h>
#include <icons/back.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <widgets/label.h>
#include <fmt/core.h>

// Local includes
#include "utils.h"
#include "icons/settings.h"
#include "battery.h"
#include "menus/batterymenu.h"
#include "globals.h"
#include "displays/menus/batterymenu.h"
#include "accessors/settingsaccessors.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_BATTERY_CALIBRATE[] = "Calibrate Voltages";
constexpr char TEXT_VOLTAGECALIBRATION_30V[] = "Calibrate 30.0V";
constexpr char TEXT_VOLTAGECALIBRATION_50V[] = "Calibrate 50.0V";
constexpr char TEXT_VOLTAGECALIBRATION_VALUE_30_FRONT[] = "30V Front";
constexpr char TEXT_VOLTAGECALIBRATION_VALUE_30_BACK[] = "30V Back";
constexpr char TEXT_VOLTAGECALIBRATION_VALUE_50_FRONT[] = "50V Front";
constexpr char TEXT_VOLTAGECALIBRATION_VALUE_50_BACK[] = "50V Back";
constexpr char TEXT_BATTERY_APPLYCALIB[] = "Apply calibration";
constexpr char TEXT_VOLTAGECALIBRATION_RESET[] = "Reset calibration";
constexpr char TEXT_BACK[] = "Back";

class Save30VCalibrationAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        settings.battery.front30VoltCalibration = controllers.front.feedback.batVoltage;
        settings.battery.back30VoltCalibration = controllers.back.feedback.batVoltage;
        saveSettings();
    }
};

class Save50VCalibrationAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        settings.battery.front50VoltCalibration = controllers.front.feedback.batVoltage;
        settings.battery.back50VoltCalibration = controllers.back.feedback.batVoltage;
        saveSettings();
    }
};

class ResetCalibrationAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        settings.battery.front30VoltCalibration = 3000;
        settings.battery.back30VoltCalibration = 3000;
        settings.battery.front50VoltCalibration = 5000;
        settings.battery.back50VoltCalibration = 5000;
        saveSettings();
    }
};

float convertToFloat(int16_t value)
{
    return value/100.;
}

class BatteryVoltageCalibrationFront30VText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("30V Front: {}", convertToFloat(settings.battery.front30VoltCalibration));
    }
};

class BatteryVoltageCalibrationBack30VText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("30V Back: {}", convertToFloat(settings.battery.back30VoltCalibration));
    }
};

class BatteryVoltageCalibrationFront50VText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("50V Front: {}", convertToFloat(settings.battery.front50VoltCalibration));
    }
};

class BatteryVoltageCalibrationBack50VText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("50V Back: {}", convertToFloat(settings.battery.back50VoltCalibration));
    }
};

class BatteryVoltageCalibratedText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        if (settings.battery.applyCalibration)
            return fmt::format("F{:.2f}V B{:.2f}", controllers.front.getCalibratedVoltage(), controllers.back.getCalibratedVoltage());
        else
            return "Not activated";
    }
};
} // namespace

CalibrateVoltageDisplay::CalibrateVoltageDisplay()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_30V>,          Save30VCalibrationAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_50V>,          Save50VCalibrationAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_APPLYCALIB>,              BobbyCheckbox, BatteryApplyCalibrationAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                            SwitchScreenAction<BatteryMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();

    constructMenuItem<makeComponent<MenuItem, EmptyText,                                        DummyAction>>();

    constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationFront30VText,            DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationBack30VText,             DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationFront50VText,            DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationBack50VText,             DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibratedText,                     DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_RESET>,        ResetCalibrationAction>>();
}

std::string CalibrateVoltageDisplay::text() const
{
    return TEXT_BATTERY_CALIBRATE;
}

void CalibrateVoltageDisplay::back()
{
    espgui::switchScreen<BatteryMenu>();
}
