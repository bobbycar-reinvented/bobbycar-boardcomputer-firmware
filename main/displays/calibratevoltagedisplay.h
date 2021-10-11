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
#include "battery.h"
#include "menus/batterymenu.h"
#include "widgets/label.h"
#include "globals.h"

using namespace espgui;

namespace  {
    class CalibrateVoltageDisplay;
    class BatteryMenu;

    class Save30VCalibrationAction : public virtual ActionInterface
    {
    public:
        void triggered() override {
            settings.battery.front30VoltCalibration = controllers.front.feedback.batVoltage;
            settings.battery.back30VoltCalibration = controllers.back.feedback.batVoltage;
            saveSettings();
        }
    };

    class Save50VCalibrationAction : public virtual ActionInterface
    {
    public:
        void triggered() override {
            settings.battery.front50VoltCalibration = controllers.front.feedback.batVoltage;
            settings.battery.back50VoltCalibration = controllers.back.feedback.batVoltage;
            saveSettings();
        }
    };

    class ResetCalibrationAction : public virtual ActionInterface
    {
    public:
        void triggered() override {
            settings.battery.front30VoltCalibration = 3000;
            settings.battery.back30VoltCalibration = 3000;
            settings.battery.front50VoltCalibration = 5000;
            settings.battery.back50VoltCalibration = 5000;
            saveSettings();
        }
    };

    class BatteryVoltageCalibrationFront30VText : public virtual TextInterface { public: std::string text() const override { return fmt::format("30V Front: {:.2f}V", fixBatVoltage(settings.battery.front30VoltCalibration)); } };
    class BatteryVoltageCalibrationBack30VText : public virtual TextInterface { public: std::string text() const override { return fmt::format("30V Back: {:.2f}V", fixBatVoltage(settings.battery.back30VoltCalibration)); } };
    class BatteryVoltageCalibrationFront50VText : public virtual TextInterface { public: std::string text() const override { return fmt::format("50V Front: {:.2f}V", fixBatVoltage(settings.battery.front50VoltCalibration)); } };
    class BatteryVoltageCalibrationBack50VText : public virtual TextInterface { public: std::string text() const override { return fmt::format("50V Back: {:.2f}V", fixBatVoltage(settings.battery.back50VoltCalibration)); } };
    class BatteryVoltageCalibratedText : public virtual TextInterface { public: std::string text() const override { if (settings.battery.applyCalibration) return fmt::format("F{:.2f}V B{:.2f}", fixFrontBatVoltage(controllers.front.feedback.batVoltage), fixFrontBatVoltage(controllers.back.feedback.batVoltage)); else return "Not activated"; } };
}

namespace  {
    class CalibrateVoltageDisplay :
            public MenuDisplay,
            public StaticText<TEXT_BATTERY_CALIBRATE>,
            public BackActionInterface<SwitchScreenAction<BatteryMenu>>
    {
    public:
        CalibrateVoltageDisplay()
        {
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_30V>,          Save30VCalibrationAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_50V>,          Save50VCalibrationAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY_APPLYCALIB>,              ToggleBoolAction, CheckboxIcon, BatteryApplyCalibrationAccessor>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                            SwitchScreenAction<BatteryMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();

            constructMenuItem<makeComponent<MenuItem, EmptyText,                                        DummyAction>>();

            constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationFront30VText,            DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationBack30VText,             DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationFront50VText,            DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibrationBack50VText,             DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, BatteryVoltageCalibratedText,                     DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGECALIBRATION_RESET>,        ResetCalibrationAction>>();
        }
    };
} // Namespace
