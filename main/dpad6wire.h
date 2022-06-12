#pragma once

// system includes
#include <cstdint>

#ifdef FEATURE_DPAD_6WIRESW
namespace dpad6wire {
void init();
void update();
constexpr const uint8_t BUTTON_COUNT = 10;
} // namespace dpad6wire
#endif
