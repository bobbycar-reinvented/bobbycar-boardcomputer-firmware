#pragma once

// 3rdparty lib includes
#ifdef FEATURE_OTA
#include <espasyncota.h>
#endif
#include <delayedconstruction.h>

// local includes

#ifdef FEATURE_OTA
extern cpputils::DelayedConstruction<EspAsyncOta> asyncOta;
extern bool asyncOtaTaskStarted;

void initOta();
void handleOta();
tl::expected<void, std::string> triggerOta(std::string_view url);
#endif
