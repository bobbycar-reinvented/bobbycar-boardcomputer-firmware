#include "taskmanager.h"

#include "sdkconfig.h"

// system includes
#include <chrono>

// esp-idf includes
#include <esp_log.h>

// local includes
#include "wifi_bobbycar.h"
#ifdef FEATURE_ROTARY
#include "rotary.h"
#endif
#ifdef FEATURE_MOSFETS
#include "mosfets.h"
#endif
#include "time_bobbycar.h"
#include "potis.h"
#ifdef FEATURE_BLUETOOTH
#include "bluetooth_bobby.h"
#ifdef FEATURE_BMS
#include "bmsutils.h"
#endif
#endif
#ifdef FEATURE_CAN
#include "can.h"
#endif
#include "debuginputhandler.h"
#ifdef FEATURE_SERIAL
#include "serial_bobby.h"
#endif
#include "ota.h"
#include "ble_bobby.h"
#include "webserver.h"
#include "ledstrip.h"
#include "espnowfunctions.h"
#include "cloud.h"
#include "udpcloud.h"
#include "modes.h"
#include "drivingstatistics.h"
#include "dnsannounce.h"
#include "screens.h"
#include "utils.h"
#include "feedbackemulator.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "TASKS";

void not_needed() {}

BobbySchedulerTask schedulerTasksArr[] {
    BobbySchedulerTask { "wifi",           wifi_begin,            wifi_update,             350ms, false },
#if defined(FEATURE_DPAD) || defined(FEATURE_DPAD_3WIRESW) || defined(FEATURE_DPAD_5WIRESW) || defined(FEATURE_DPAD_5WIRESW_2OUT) || defined(FEATURE_DPAD_6WIRESW) || defined(DPAD_BOARDCOMPUTER_V2)
    BobbySchedulerTask { bobbydpad::dpad_name,  bobbydpad::dpad_init,       bobbydpad::dpad_update,       20ms, true  },
#endif
#ifdef FEATURE_ROTARY
    BobbySchedulerTask { "rotary",         initRotary,            updateRotary,            20ms, false },
#endif
#ifdef FEATURE_MOSFETS
    BobbySchedulerTask { "mosfets",        init_mosfets,          update_mosfets,          100ms, false },
#endif
    BobbySchedulerTask { "time",           initTime,              updateTime,              250ms, false },
    BobbySchedulerTask { "potis",          initPotis,             readPotis,               20ms, false  },
#ifdef FEATURE_BLUETOOTH
    BobbySchedulerTask { "bluetooth",      bluetooth_init,        bluetooth_update,        100ms, false },
#ifdef FEATURE_BMS
    BobbySchedulerTask { "bms",            bms::init,             bms::update,             100ms, false },
#endif
#endif
#ifdef FEATURE_CAN
    BobbySchedulerTask { "can",            can::initCan,          can::updateCan,          8ms, false  },
#endif
    BobbySchedulerTask { "debuginput",     initDebugInput,        handleDebugInput,        75ms, true  },
#ifdef FEATURE_SERIAL
    BobbySchedulerTask { "serial",         initSerial,            updateSerial,            50ms, false  },
#endif
    BobbySchedulerTask { "ota",            initOta,               handleOta,               100ms, false },
    BobbySchedulerTask { "ble",            initBle,               handleBle,               125ms, false },
    BobbySchedulerTask { "webserver",      initWebserver,         handleWebserver,         125ms, false },
    BobbySchedulerTask { "ledstrip",       initLedStrip,          updateLedStrip,          10ms, false },
    BobbySchedulerTask { "espnow",         espnow::initESPNow,    espnow::handle,          150ms, false },
    BobbySchedulerTask { "cloud",          initCloud,             updateCloud,             60ms, false },
    BobbySchedulerTask { "udpcloud",       udpcloud::udpCloudInit, udpcloud::udpCloudUpdate, 60ms, false },
    BobbySchedulerTask { "drivingmode",    initDrivingMode,       updateDrivingMode,       8ms, false },
    BobbySchedulerTask { "drivingstatistics", initStatistics,     calculateStatistics,     175ms, false },
    BobbySchedulerTask { "dnsannounce",    init_dns_announce,     handle_dns_announce,     500ms, false },
    BobbySchedulerTask { "updateDisp",     not_needed,            bobby::updateDisplay,    20ms, true },
    BobbySchedulerTask { "redrawDisp",     not_needed,            bobby::redrawDisplay,    16ms, true },
    BobbySchedulerTask { "feedbackEmulator", feedbackemulator::init, feedbackemulator::update, 500ms, false},
};
} // namespace

cpputils::ArrayView<BobbySchedulerTask> schedulerTasks{std::begin(schedulerTasksArr), std::end(schedulerTasksArr)};

const BobbySchedulerTask &drivingModeTask = []() -> const BobbySchedulerTask & {
    auto iter = std::find_if(std::begin(schedulerTasksArr), std::end(schedulerTasksArr), [](const BobbySchedulerTask &task){
        return std::string_view{task.name()} == "drivingmode";
    });
    return *iter;
}();

void sched_pushStats(bool printTasks)
{
    if (printTasks)
        ESP_LOGI(TAG, "begin listing tasks...");

    for (auto &schedulerTask : schedulerTasks)
        schedulerTask.pushStats(printTasks);

    if (printTasks)
        ESP_LOGI(TAG, "end listing tasks");
}

tl::expected<bool, std::string> checkInitializedByName(const std::string& name)
{
    for (auto &schedulerTask : schedulerTasks)
    {
        // ESP_LOGE(TAG, "%s == %s", schedulerTask.name(), name.c_str());
        if (schedulerTask.name() == name)
            return schedulerTask.isInitialized();
    }
    return tl::make_unexpected("Task not found: " + std::string{name});
}

bool checkEnabledByName(const std::string& name) {
    bool enabled = true;
    // iterate over all feature flags (runForEveryFeature())
    configs.callForEveryFeature([&](ConfiguredFeatureFlag &feature) {
        if (feature.getTaskName() == name)
            enabled = feature.isEnabled.value();
        return false;
    });
    return enabled;
}

void reload_tasks()
{
    for (auto &task : schedulerTasks)
    {
        if (checkEnabledByName(task.name()) && !task.isInitialized())
        {
            task.setup();
        }
    }
}
