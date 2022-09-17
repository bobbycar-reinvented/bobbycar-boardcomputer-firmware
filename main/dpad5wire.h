#pragma once

// system includes
#include <cstdint>

#ifdef FEATURE_DPAD_5WIRESW
namespace dpad5wire {
void init();
void update();
constexpr const uint8_t BUTTON_COUNT = 8;
} // namespace dpad5wire
#endif
