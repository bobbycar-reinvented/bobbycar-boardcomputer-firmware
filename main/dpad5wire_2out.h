#pragma once

// system includes
#include <cstdint>

#ifdef FEATURE_DPAD_5WIRESW_2OUT
namespace dpad5wire_2out {
void init();
void update();
constexpr const uint8_t BUTTON_COUNT = 12;
} // namespace dpad5wire_2out
#endif
