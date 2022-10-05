#include "udpcloud.h"

// 3rd party includes
#include <ArduinoJson.h>
#include <FastLED.h>
#include <esp_ota_ops.h>
#include <espwifistack.h>

// local includes
#include "udpsender.h"
#include "esp_log.h"
#include "fmt/format.h"
#include "globals.h"
#include "utils.h"
#include "lwip/dns.h"
#include "espchrono.h"
#include "battery.h"
#include "drivingstatistics.h"
#include "newsettings.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "bobbycloud";

espchrono::millis_clock::time_point timestampLastFailed;
espchrono::millis_clock::time_point lastSend;
} // namespace

// Little "flash" on statusdisplay when udp stuff is happening
bool visualSendUdpPacket;

void udpCloudInit()
{

}

void udpCloudUpdate()
{
    if (!configs.feature.udpcloud.isEnabled.value())
        return;

    if (configs.udpCloudSettings.udpCloudEnabled.value() && configs.udpCloudSettings.udpUid.touched())
        sendUdpCloudPacket();
}

std::string buildUdpCloudJson()
{
    static std::string version_string;
    if (version_string.empty() || version_string == "-")
    {
        if (const esp_app_desc_t *app_desc = esp_ota_get_app_description())
        {
            version_string = app_desc->version;
        }
        else
        {
            version_string = "-";
        }
    }
    StaticJsonDocument<1024> doc;
    std::string buf;
    const auto uptime = espchrono::millis_clock::now().time_since_epoch() / 1ms;

    float watt{0};
    const auto avgVoltage = controllers.getAvgVoltage();
    if(avgVoltage)
        watt = sumCurrent * *avgVoltage;

    // const auto w_per_kmh = watt / avgSpeedKmh;

    // User ID
    doc["uid"] = configs.udpCloudSettings.udpUid.value();
    doc["upt"] = uptime;

    const auto addController = [&](const Controller &controller, const bool isBack) {
        if (controller.feedbackValid)
        {
            auto arr = doc.createNestedObject(!isBack ? "f":"b");
            // Voltage
            arr["V"] = controller.getCalibratedVoltage();

            // Amperes
            arr["lA"] = fixCurrent(controller.feedback.left.dcLink);
            arr["rA"] = fixCurrent(controller.feedback.right.dcLink);

            // Temperature
            arr[!isBack ? "fT":"bT"] = fixBoardTemp(controller.feedback.boardTemp);

            // Errors
            arr[!isBack ? "flE":"blE"] = controller.feedback.left.error;
            arr[!isBack ? "frE":"brE"] = controller.feedback.right.error;

            // Speed
            arr[!isBack ? "flS":"blS"] = convertToKmh(controller.feedback.left.speed) * (controller.invertLeft?-1:1);
            arr[!isBack ? "frS":"brS"] = convertToKmh(controller.feedback.right.speed) * (controller.invertRight?-1:1);
        }
        else
        {
            doc[!isBack ? "f":"b"] = nullptr;
        }
    };

    addController(controllers.front, false);
    addController(controllers.back, true);

    // Potis
    {
        auto arr = doc.createNestedObject("p");
        if (gas)
            arr["g"] = *gas;
        if (raw_gas)
            arr["rg"] = *raw_gas;
        if (brems)
            arr["b"] = *brems;
        if (raw_brems)
            arr["rb"] = *raw_brems;
    }

    // Statistics
    if(avgVoltage)
    {
        doc["bP"] = getBatteryPercentage(*avgVoltage, BatteryCellType(configs.battery.cellType.value()));
        doc["bV"] = *avgVoltage;
    }
    doc["l"] = isLocked;
    doc["mN"] = drivingStatistics.meters_driven;
    doc["mT"] = drivingStatistics.totalMeters;
    doc["dT"] = drivingStatistics.currentDrivingTime / 1ms;
    doc["cW"] = watt;
    doc["wN"] = drivingStatistics.wh_used;
    doc["wL"] = getRemainingWattHours();
    doc["kmL"] = getRemainingWattHours() / configs.battery.watthoursPerKilometer.value();
    doc["ver"] = version_string.substr(0, 6);

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

    if (configs.udpCloudHost.value().empty())
    {
        visualSendUdpPacket = false;
        return;
    }

    if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
    {
        visualSendUdpPacket = false;
        return;
    }

    if(espchrono::ago(lastSend) / 1000ms > configs.boardcomputerHardware.timersSettings.udpSendRateMs.value())
    {
        lastSend = espchrono::millis_clock::now();

        ip_addr_t udpCloudIp;

        if (const auto res = dns_gethostbyname(configs.udpCloudHost.value().c_str(), &udpCloudIp, nullptr, nullptr); res != ERR_OK)
        {
            ESP_LOGE(TAG, "dns_gethostbyname() failed because: %i", res);
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

        sockaddr_in receipient;
        receipient.sin_port = htons(24242);
        receipient.sin_addr.s_addr = udpCloudIp.u_addr.ip4.addr;
        receipient.sin_family = AF_INET;

        wifi_stack::UdpSender udpCloudSender;
        const auto buf = buildUdpCloudJson();

        if (const auto result = udpCloudSender.send(receipient, buf); !result)
        {
            timestampLastFailed = espchrono::millis_clock::now();
            ESP_LOGE(TAG, "send to cloud failed: %.*s (ip=%s)", result.error().size(), result.error().data(), wifi_stack::toString(udpCloudIp.u_addr.ip4).c_str());
        }

        ESP_LOGI(TAG, "%s", buf.c_str());

        visualSendUdpPacket = !visualSendUdpPacket;
    }
}
