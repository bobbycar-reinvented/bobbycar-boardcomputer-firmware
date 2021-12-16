#pragma once

#include <cstdint>
#include <esp_now.h>

namespace espnow {
class IESPNowW {
  public:
    virtual int add_peer(uint8_t *mac, int channel = 0) = 0;
    virtual int remove_peer(uint8_t *mac) = 0;
    virtual int send_message(uint8_t *mac, uint8_t *data, size_t datalen) = 0;
    virtual int init() { return esp_now_init(); }
    int reg_send_cb(esp_now_send_cb_t cb) {
        return esp_now_register_send_cb(cb);
    }
    int reg_recv_cb(esp_now_recv_cb_t cb) {
        return esp_now_register_recv_cb(cb);
    }
    int unreg_send_cb() { return esp_now_unregister_send_cb(); }
    int unreg_recv_cb() { return esp_now_unregister_recv_cb(); }
};

extern IESPNowW &ESPNow;
} // namespace
