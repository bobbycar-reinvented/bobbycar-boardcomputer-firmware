constexpr const char * const TAG = "BOBBY";

// esp-idf includes
#include <esp_pm.h>
#include <esp_chip_info.h>
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>
using namespace std::chrono_literals;
#include <tickchrono.h>
#include <espstrutils.h>
#include <screenmanager.h>

// local includes
#include "globals.h"
#include "screens.h"
#include "presets.h"
#include "statistics.h"
#ifdef FEATURE_JOYSTICK
#include "modes/wheelchairmode.h"
#else
#include "modes/defaultmode.h"
#endif
#include "screens/lockscreen.h"
#include "screens/recoverymenu.h"
#include "screens/setup/information.h"
#include "screens/setup/basic_buttons.h"
#include "screens/setup/calibrate_potis.h"
#include "screens/statusdisplay.h"
#include "newsettings.h"
#include "taskmanager.h"
#include "defaultstatusdisplay.h"
#include "globallock.h"

#define BOOT_PROGRESS(s) \
    bobby::set_boot_msg(s); \
    ESP_LOGE("BOOT", "%s (%lldms, %lldms since last one)", s, espchrono::ago(boot_start) / 1ms, espchrono::ago(last_boot_label) / 1ms); \
    last_boot_label = espchrono::millis_clock::now();

namespace {
espchrono::millis_clock::time_point lastStatsPush;
std::optional<espchrono::millis_clock::time_point> lastStatsUpdate;
RTC_NOINIT_ATTR bool recovery;
} // namespace

extern "C" [[noreturn]] void app_main()
{
    using namespace bobby;

    const auto boot_start = espchrono::millis_clock::now();
    auto last_boot_label = boot_start;

    if (const auto reset_reason = esp_reset_reason(); reset_reason == ESP_RST_POWERON)
    {
        recovery = false;
    }

    if (recovery)
    {
        bobby::initScreen();

        ESP_LOGE(TAG, "Recovery mode (%s)", espcpputils::toString(esp_reset_reason()).c_str());
        BOOT_PROGRESS("Entering recovery mode");

        if (const auto result = configs.init("bobbycar"); result != ESP_OK)
            ESP_LOGE(TAG, "config_init_settings() failed with %s", esp_err_to_name(result));

        for (auto &task : bobby::schedulerTasks)
        {
            task.setup(recovery);
        }

        espgui::switchScreen<bobby::RecoveryMenu>();

        recovery = false;

        while (true)
        {
            for (auto &schedulerTask : bobby::schedulerTasks)
            {
                if (schedulerTask.isInitialized())
                    schedulerTask.loop();
            }

            //espcpputils::delay(1ms);
        };
    }
    else
    {
        recovery = true;
    }

    BOOT_PROGRESS("settings");

    if (const auto result = configs.init("bobbycar"); result != ESP_OK)
        ESP_LOGE(TAG, "config_init_settings() failed with %s", esp_err_to_name(result));
    else
        ESP_LOGI(TAG, "config_init_settings() succeeded");

    BOOT_PROGRESS("init screen");
    bobby::initScreen();

    BOOT_PROGRESS("profile settings");
    profileSettings = presets::defaultProfileSettings;

    if (settingsPersister.init())
    {
        if (!settingsPersister.openProfile(0))
            ESP_LOGE("BOBBY", "openProfile(0) failed");

        loadProfileSettings();
    }
    else
        ESP_LOGE("BOBBY", "init() failed");

    global_lock.construct();

    BOOT_PROGRESS("starting tasks");
    for (auto &task : schedulerTasks)
    {
        if (checkEnabledByName(task.name()))
        {
            BOOT_PROGRESS(task.name());
            task.setup(false);
        }
    }

#ifdef FEATURE_JOYSTICK
    currentMode = &modes::wheelchairMode;
#else
    currentMode = &modes::defaultMode;
#endif

    BOOT_PROGRESS("switchScreen");

    if (const auto result = checkIfInCalibration(); result)
    {
        switch(*result)
        {
        case SetupStep::INFORMATION:
            BOOT_PROGRESS("Calibtration");
            espgui::switchScreen<SetupInformationDisplay>();
            break;
        case SetupStep::BASIC_BUTTONS:
            BOOT_PROGRESS("Calibtration");
            espgui::switchScreen<SetupBasicButtonsDisplay>(true);
            break;
        case SetupStep::CALIBRATE_POTIS:
            espgui::switchScreen<SetupCalibratePotisDisplay>(true);
            break;
        default:;
        }
    }
    else if (configs.lockscreen.keepLockedAfterReboot.value() && configs.lockscreen.locked.value())
    {
        BOOT_PROGRESS("Locked");
        espgui::pushScreen<Lockscreen>(true);
    }
    else
    {
        BOOT_PROGRESS("StatusDisplay")
        switchToDefaultStatusDisplay();
    }

    esp_chip_info(&chip_info);
    esp_pm_get_configuration(&pm_config);

    if (const std::optional<uint32_t> value = configs.lockscreen.rememberMe.value(); value)
    {
        // value is savedCentimeters of the last time the lockscreen was unlocked
        const uint32_t savedCentimeters = configs.savedStatistics.totalCentimeters.value();
        const auto diff_in_cm = savedCentimeters - *value;

        // simplified should be true if diff is more than 15km
        simplified = diff_in_cm > 15 * 100 * 1000; // 15km * 100cm/km * 1000
        ESP_LOGW(TAG, "Remember me: %lucm, saved: %lucm", *value, savedCentimeters);
        ESP_LOGW(TAG, "Diff: %lucm", diff_in_cm);
        ESP_LOGW(TAG, "Simplified is %s", simplified ? "enabled" : "disabled");
    }

    BOOT_PROGRESS("main loop");
    ESP_LOGI(TAG, "Entering main loop...");

    while (true)
    {
        const auto now = espchrono::millis_clock::now();

        if (recovery && now.time_since_epoch() > 5s)
        {
            ESP_LOGI(TAG, "Booting successful, disabling recovery...");
            recovery = false;
        }

//       if (!heap_caps_check_integrity_all(true))
//            ESP_LOGW(TAG, "OIS IM OARSCH!!!!!");

        for (auto &schedulerTask : schedulerTasks)
        {
            if (schedulerTask.isInitialized())
                schedulerTask.loop();
            else if (schedulerTask.hasDelayedInit())
                schedulerTask.delayedInit();
        }

        if (!lastStatsUpdate || now - *lastStatsUpdate >= 1000ms/configs.boardcomputerHardware.timersSettings.statsUpdateRate.value())
        {
            updateAccumulators();
            statistics::pushStats();
            lastStatsUpdate = now;
        }

        if (now - lastStatsPush >= 1s)
        {
            sched_pushStats(false);

            lastStatsPush = now;
        }

        if (!battery::bootBatPercentage)
        {
            if(controllers.front.feedbackValid && controllers.back.feedbackValid)
            {
                if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
                {
                    if (avgVoltage > 30)
                    {
                        battery::bootBatPercentage = battery::getBatteryPercentage(*avgVoltage, configs.battery.cellType.value());
                        battery::bootBatWh = battery::getRemainingWattHours();
                    }
                }
            }
        }

        //espcpputils::delay(1ms);
    }
}
