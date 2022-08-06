#pragma once

// system includes
#include <cstdint>

#ifdef DPAD_BOARDCOMPUTER_V2
namespace dpad_boardcomputer_v2 {
void init();
void update();
constexpr const uint8_t BUTTON_COUNT = 16;
} // namespace dpad_boardcomputer_v2
#endif
