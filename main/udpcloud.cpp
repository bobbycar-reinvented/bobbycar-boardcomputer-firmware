#include "udpcloud.h"

// system includes
#include <esp_log.h>
#include <lwip/dns.h>

// 3rd party includes
#include <espchrono.h>
#include <espwifistack.h>
#include <fmt/format.h>
#include <delayedconstruction.h>

// local includes
#include "cloudstats.h"
#include "newsettings.h"
#include "udpsender.h"

using namespace std::chrono_literals;

namespace bobby::udpcloud {

namespace {
constexpr const char *const TAG = "bobbycloud";

espchrono::millis_clock::time_point timestampLastFailed;
espchrono::millis_clock::time_point lastSend;
espchrono::millis_clock::time_point lastDNSQuery;

std::optional<sockaddr_in> receipient;
ip_addr_t udpCloudIp;
cpputils::DelayedConstruction<wifi_stack::UdpSender> udpCloudSender;

bool visualSendUdpPacket{false};

bool got_ip{false};
} // namespace

void udpCloudInit()
{
    visualSendUdpPacket = false;
    got_ip = false;
}

void udpCloudUpdate()
{
    if (!configs.feature.udpcloud.isEnabled.value() || !configs.udpCloudSettings.udpCloudEnabled.value())
    {
        cloudstats::udpNeedsConstruction(false);
        visualSendUdpPacket = false;
        return;
    }

    if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
    {
        cloudstats::udpNeedsConstruction(false);
        visualSendUdpPacket = false;
        return;
    }

    if (espchrono::ago(lastDNSQuery) > 10s || !receipient.has_value())
    {
        lastDNSQuery = espchrono::millis_clock::now();
        receipient = sockaddr_in{};
        if (const auto res = dns_gethostbyname(configs.udpCloudSettings.udpCloudHost.value().c_str(), &udpCloudIp,
                                               nullptr, nullptr); res != ERR_OK)
        {
            ESP_LOGE(TAG, "dns_gethostbyname() failed because: (%s) (%i)", lwip_strerr(res), res);
            timestampLastFailed = espchrono::millis_clock::now();
            visualSendUdpPacket = false;
            return;
        }

        if (udpCloudIp.type != IPADDR_TYPE_V4)
        {
            ESP_LOGE(TAG, "unsupported ip type: %hhu", udpCloudIp.type);
            timestampLastFailed = espchrono::millis_clock::now();
            visualSendUdpPacket = false;
            return;
        }

        (*receipient).sin_port = htons(configs.udpCloudSettings.udpCloudPort.value());
        (*receipient).sin_addr.s_addr = udpCloudIp.u_addr.ip4.addr;
        (*receipient).sin_family = AF_INET;

        got_ip = true;
    }

    if (espchrono::ago(timestampLastFailed) < 2s)
    {
        visualSendUdpPacket = false;
        return;
    }

    if (
            configs.udpCloudSettings.udpCloudHost.value().empty() ||
            configs.udpCloudSettings.udpCloudPort.value() < 80 ||
            !configs.udpCloudSettings.udpToken.touched() ||
            configs.udpCloudSettings.udpToken.value().empty() ||
            !receipient.has_value()
        )
    {
        visualSendUdpPacket = false;
        return;
    }

    if (espchrono::ago(lastSend) / 1ms > configs.boardcomputerHardware.timersSettings.udpSendRateMs.value())
    {
        sendUdpCloudPacket();
    }
}

void sendUdpCloudPacket()
{
    if (!got_ip)
        return;

    cloudstats::udpNeedsConstruction(true);

    if (!udpCloudSender)
        udpCloudSender.construct();

    if (const auto json = cloudstats::buildCloudJson(); json)
    {
        if (const auto result = udpCloudSender->send(*receipient, *json); !result)
        {
            timestampLastFailed = espchrono::millis_clock::now();
            ESP_LOGE(TAG, "send to cloud failed: %.*s (ip=%s)", result.error().size(), result.error().data(),
                     wifi_stack::toString(udpCloudIp.u_addr.ip4).c_str());
        }
        else
        {
            visualSendUdpPacket = !visualSendUdpPacket;
            lastSend = espchrono::millis_clock::now();
        }
    }
}

bool blink()
{
    return visualSendUdpPacket;
}

} // namespace udpcloud
