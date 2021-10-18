#pragma once

#include "icon.h"

namespace bobbyicons {
#if defined(FEATURE_BLUETOOTH) || defined(FEATURE_BLE)
extern const espgui::Icon<24, 24> bluetooth;
#endif
} // namespace bobbyicons
