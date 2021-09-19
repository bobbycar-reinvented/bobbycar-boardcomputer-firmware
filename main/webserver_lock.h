#pragma once

// 3rdparty lib includes
#include <delayedconstruction.h>
#include <wrappers/mutex_semaphore.h>

namespace {

cpputils::DelayedConstruction<espcpputils::mutex_semaphore> webserver_lock;

} // namespace
