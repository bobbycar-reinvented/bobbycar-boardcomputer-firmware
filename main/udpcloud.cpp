#include "udpcloud.h"

// system includes
#include <esp_log.h>
#include <esp_ota_ops.h>
#include <lwip/dns.h>

// 3rd party includes
#include <ArduinoJson.h>
#include <FastLED.h>
#include <espchrono.h>
#include <espwifistack.h>
#include <fmt/format.h>

// local includes
#include "battery.h"
#include "drivingstatistics.h"
#include "globals.h"
#include "newsettings.h"
#include "taskmanager.h"
#include "udpsender.h"
#include "utils.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "bobbycloud";

espchrono::millis_clock::time_point timestampLastFailed;
espchrono::millis_clock::time_point lastSend;
espchrono::millis_clock::time_point lastDNSQuery;

uint8_t packageType{0}; // cycle through packages.
std::optional<sockaddr_in> receipient;
ip_addr_t udpCloudIp;
} // namespace

// Little "flash" on statusdisplay when udp stuff is happening
bool visualSendUdpPacket;

void udpCloudInit() {}

void udpCloudUpdate()
{
    if (!configs.feature.udpcloud.isEnabled.value())
        return;

    if (configs.udpCloudSettings.udpCloudEnabled.value() && configs.udpCloudSettings.udpToken.touched())
        sendUdpCloudPacket();

    if (espchrono::ago(lastDNSQuery) > 10s || !receipient.has_value())
    {
        lastDNSQuery = espchrono::millis_clock::now();
        receipient = sockaddr_in{};
        if (const auto res = dns_gethostbyname(configs.udpCloudSettings.udpCloudHost.value().c_str(), &udpCloudIp, nullptr, nullptr); res != ERR_OK)
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
    }
}

std::optional<std::string> buildUdpCloudJson()
{
    StaticJsonDocument<512> doc;

    switch (++packageType)
    {
    default:
        packageType = 0;
    case 0:
    {
        // uptime, potis
        const auto uptime = espchrono::millis_clock::now().time_since_epoch() / 1ms;
        doc["upt"] = uptime;

        if (gas)
            doc["pcg"] = *gas; // poti calculated gas
        if (raw_gas)
            doc["prg"] = *raw_gas; // poti raw gas
        if (brems)
            doc["pcb"] = *brems; // poti calculated brems
        if (raw_brems)
            doc["prb"] = *raw_brems; // poti raw brems

        doc["loc"] = isLocked;
        doc["mdr"] = drivingStatistics.meters_driven;
        doc["mdt"] = drivingStatistics.totalMeters;
        doc["cdt"] = drivingStatistics.currentDrivingTime / 1ms;
        doc["sha"] = GIT_REV;
        break;
    }
    case 1:
    case 4:
    {

        if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
        {
            doc["bap"] = getBatteryPercentage(*avgVoltage, BatteryCellType(configs.battery.cellType.value()));
            doc["bav"] = *avgVoltage; // battery voltage
            doc["pwr"] = sumCurrent * *avgVoltage; // total watt
        }
        doc["whl"] = getRemainingWattHours(); // watt hours left
        doc["kml"] = getRemainingWattHours() / configs.battery.watthoursPerKilometer.value(); // calculated kilometers left
        doc["ekm"] = getEstimatedKmLeft(); // kilometers left live calculation
        break;
    }
    case 2:
    case 5:
    {
        const auto &controller = controllers.front;
        if (controller.feedbackValid)
        {
            doc["fbv"] = controller.getCalibratedVoltage();

            // Amperes
            doc["fla"] = fixCurrent(controller.feedback.left.dcLink);
            doc["fra"] = fixCurrent(controller.feedback.right.dcLink);

            // Temperature
            doc["fbt"] = fixBoardTemp(controller.feedback.boardTemp);

            // Errors
            doc["fle"] = controller.feedback.left.error;
            doc["fre"] = controller.feedback.right.error;

            // Speed
            doc["fls"] = convertToKmh(controller.feedback.left.speed) * (controller.invertLeft?-1:1);
            doc["frs"] = convertToKmh(controller.feedback.right.speed) * (controller.invertRight?-1:1);
        }
        else
        {
            return std::nullopt;
        }
        break;
    }
    case 3:
    case 6:
    {
        const auto &controller = controllers.back;
        if (controller.feedbackValid)
        {
            doc["bbv"] = controller.getCalibratedVoltage();

            // Amperes
            doc["bla"] = fixCurrent(controller.feedback.left.dcLink);
            doc["bra"] = fixCurrent(controller.feedback.right.dcLink);

            // Temperature
            doc["bbt"] = fixBoardTemp(controller.feedback.boardTemp);

            // Errors
            doc["ble"] = controller.feedback.left.error;
            doc["bre"] = controller.feedback.right.error;

            // Speed
            doc["bls"] = convertToKmh(controller.feedback.left.speed) * (controller.invertLeft?-1:1);
            doc["brs"] = convertToKmh(controller.feedback.right.speed) * (controller.invertRight?-1:1);
        }
        else
        {
            return std::nullopt;
        }
        break;
    }
    }

    // if empty, return empty string
    if (doc.isNull())
    {
        return std::nullopt;
    }

    doc["__t"] = configs.udpCloudSettings.udpToken.value();
    doc["per"] = drivingModeTask.callCount();

    std::string buf;
    serializeJson(doc, buf);
    return buf;
}

void sendUdpCloudPacket()
{
    if (espchrono::ago(timestampLastFailed) < 2s)
    {
        visualSendUdpPacket = false;
        return;
    }

    if (configs.udpCloudSettings.udpCloudHost.value().empty() || configs.udpCloudSettings.udpCloudPort.value() == 0)
    {
        visualSendUdpPacket = false;
        return;
    }

    if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
    {
        visualSendUdpPacket = false;
        return;
    }

    if(espchrono::ago(lastSend) / 1ms > configs.boardcomputerHardware.timersSettings.udpSendRateMs.value())
    {
        lastSend = espchrono::millis_clock::now();

        if (!receipient)
        {
            return;
        }

        wifi_stack::UdpSender udpCloudSender;
        std::string buf;

        if (const auto json = buildUdpCloudJson(); !json)
        {
            return;
        }
        else
        {
            buf = *json;
        }

        if (const auto result = udpCloudSender.send(*receipient, buf); !result)
        {
            timestampLastFailed = espchrono::millis_clock::now();
            ESP_LOGE(TAG, "send to cloud failed: %.*s (ip=%s)", result.error().size(), result.error().data(), wifi_stack::toString(udpCloudIp.u_addr.ip4).c_str());
        }

        visualSendUdpPacket = !visualSendUdpPacket;
    }
}
