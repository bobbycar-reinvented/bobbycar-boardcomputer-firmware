#pragma once
#ifdef FEATURE_ESPNOW
#include <cstdint>
#include <deque>
#include <string>

namespace espnow {
constexpr const uint8_t broadcast_address[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
struct esp_now_message_t {
    const std::string content;
    const std::string type;
};

extern std::deque<esp_now_message_t> message_queue;

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len);
void initESPNow();
void handle();
void onRecvTs(uint64_t millis);
} // namespace espnow
#endif
