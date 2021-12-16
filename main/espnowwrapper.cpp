#include "espnowwrapper.h"

#include <list>
#include <cstring>

namespace espnow {
class ESPNowW32 : public IESPNowW {
  public:
    virtual esp_err_t add_peer(uint8_t *mac, int channel);
    virtual esp_err_t remove_peer(uint8_t *mac);
    virtual esp_err_t send_message(uint8_t *mac, uint8_t *data, size_t datalen);

  private:
    std::list<esp_now_peer_info_t> peers;
};

esp_err_t ESPNowW32::add_peer(uint8_t *mac, int channel) {
    peers.push_back(esp_now_peer_info_t{});
    esp_now_peer_info_t &peer = peers.back();
    std::memcpy(peer.peer_addr, mac, sizeof(peer.peer_addr));
    peer.channel = channel;
    peer.ifidx = WIFI_IF_STA;
    auto success = esp_now_add_peer(&peers.back());
    if (success != ESP_OK)
        remove_peer(mac);
    return success;
}
esp_err_t ESPNowW32::remove_peer(uint8_t *mac) {
    // find peer in peers
    for (auto it = peers.begin(); it != peers.end();) {
        if (0 == memcmp(mac, it->peer_addr, sizeof(it->peer_addr))) {
            it = peers.erase(it); // remove it
        }
    }
    return esp_now_del_peer(mac);
}
esp_err_t ESPNowW32::send_message(uint8_t *mac, uint8_t *data, size_t datalen) {
    return esp_now_send(mac, data, datalen);
}
ESPNowW32 espnow = ESPNowW32();
IESPNowW &ESPNow = espnow;
}
