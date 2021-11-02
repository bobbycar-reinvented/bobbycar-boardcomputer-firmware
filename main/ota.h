#pragma once

// 3rdparty lib includes
#ifdef FEATURE_OTA
#include <espasyncota.h>
#endif
#include <delayedconstruction.h>

// local includes

#ifdef FEATURE_OTA
cpputils::DelayedConstruction<EspAsyncOta> asyncOta;
bool asyncOtaTaskStarted{};

void initOta();
void handleOta();
tl::expected<void, std::string> triggerOta(std::string_view url);
#endif
