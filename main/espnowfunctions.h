#pragma once
#ifdef FEATURE_ESPNOW
#include <cstdint>

namespace espnow {
constexpr const uint8_t broadcast_address[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len);
void initESPNow();
void onRecvTs(uint64_t millis);
} // namespace espnow
#endif
