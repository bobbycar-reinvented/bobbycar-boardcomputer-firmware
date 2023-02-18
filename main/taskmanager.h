#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <arrayview.h>
#include <tl/expected.hpp>

// local includes
#include "bobbyschedulertask.h"

namespace bobby {

extern cpputils::ArrayView<BobbySchedulerTask> schedulerTasks;

extern const BobbySchedulerTask &drivingModeTask;

void sched_pushStats(bool printTasks);

tl::expected<bool, std::string> checkInitializedByName(const std::string& name);

bool checkEnabledByName(const std::string& name);

void reload_tasks();

} // namespace bobby
