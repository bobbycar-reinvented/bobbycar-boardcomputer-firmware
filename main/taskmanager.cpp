#include "taskmanager.h"

// system includes
#include <iterator>
#include <chrono>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <schedulertask.h>

// local includes
#include "wifi_bobbycar.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "TASKS";

espcpputils::SchedulerTask schedulerTasksArr[] {
    espcpputils::SchedulerTask { "wifi",        wifi_begin,        wifi_update,        100ms },
};
} // namespace

cpputils::ArrayView<espcpputils::SchedulerTask> schedulerTasks{std::begin(schedulerTasksArr), std::end(schedulerTasksArr)};

void sched_pushStats(bool printTasks)
{
    if (printTasks)
        ESP_LOGI(TAG, "begin listing tasks...");

    for (auto &schedulerTask : schedulerTasks)
        schedulerTask.pushStats(printTasks);

    if (printTasks)
        ESP_LOGI(TAG, "end listing tasks");
}
