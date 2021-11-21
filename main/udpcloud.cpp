constexpr const char * const TAG = "bobbycloud";

#ifdef FEATURE_CLOUD
// 3rd party includes
#include <ArduinoJson.h>
#include <FastLED.h>
#ifdef FEATURE_OTA
#include <espcppmacros.h>
#include <espstrutils.h>
#include <esp_ota_ops.h>
#endif

// local includes
#include "udpcloud.h"
#include "udpsender.h"
#include "espwifistack.h"
#include "esp_log.h"
#include "fmt/format.h"
#include "globals.h"
#include "utils.h"
#include "lwip/dns.h"
#include "espchrono.h"
#include "battery.h"
#include "drivingstatistics.h"

using namespace std::chrono_literals;
// Little "flash" on statusdisplay when udp stuff is happening
bool visualSendUdpPacket;

espchrono::millis_clock::time_point timestampLastFailed;

void spamUdpBroadcast()
{
    wifi_stack::UdpSender sender;

    if (!sender.ready())
    {
        ESP_LOGE(TAG, "could not init udp sender!");
        return;
    }

    std::string buf;
    const auto uptime = espchrono::millis_clock::now().time_since_epoch().count();

    buf = fmt::format("uptime: {}", uptime);

    if (const auto result = sender.send(ESP_IF_WIFI_STA, 187, buf); !result)
    {
        ESP_LOGE(TAG, "broadcast failed");
    }
}

std::string buildUdpCloudJson()
{
    StaticJsonDocument<1024> doc;
    std::string buf;
    const auto uptime = espchrono::millis_clock::now().time_since_epoch().count();

    float avgVoltage = 0;
    for (auto &controller : controllers)
    {
        avgVoltage += controller.getCalibratedVoltage();
    }
    avgVoltage = avgVoltage / controllers.size();

    const auto watt = sumCurrent * avgVoltage;
    // const auto w_per_kmh = watt / avgSpeedKmh;

    // User ID
    doc["uid"] = settings.cloudSettings.udpUid;
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
    doc["bP"] = getBatteryPercentage(avgVoltage, BatteryCellType(settings.battery.cellType));
    doc["bV"] = avgVoltage;
    doc["l"] = isLocked;
    // doc["mM"] = currentMode->displayName();
    doc["mN"] = drivingStatistics.meters_driven;
    doc["mT"] = drivingStatistics.totalMeters;
    doc["dT"] = drivingStatistics.currentDrivingTime;
    doc["cW"] = watt;
    doc["wN"] = drivingStatistics.wh_used;
    doc["wL"] = getRemainingWattHours();
    doc["kmL"] = getRemainingWattHours() / settings.battery.watthoursPerKilometer;
//#ifdef FEATURE_OTA
//    if (const esp_app_desc_t *app_desc = esp_ota_get_app_description())
//    {
//        doc["ver"] = espcpputils::toHexString({app_desc->app_elf_sha256, 8});
//    }
//#else
//    doc["ver"] = "-";
//#endif

    serializeJson(doc, buf);
    return buf;
}

void sendUdpCloudPacket()
{
    EVERY_N_MILLIS(settings.boardcomputerHardware.timersSettings.udpSendRateMs) {
        if (espchrono::ago(timestampLastFailed) < 3s)
        {
            visualSendUdpPacket = false;
            return;
        }

        if (stringSettings.udpCloudUrl.empty())
        {
            visualSendUdpPacket = false;
            return;
        }

        if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
        {
            visualSendUdpPacket = false;
            return;
        }

        ip_addr_t udpCloudIp;

        if (const auto res = dns_gethostbyname(stringSettings.udpCloudUrl.c_str(), &udpCloudIp, nullptr, nullptr); res != ERR_OK)
        {
            if (res == ERR_INPROGRESS)
            {
                ESP_LOGD(TAG, "dns_gethostbyname() failed because: %i", res);
            }
            else
            {
                ESP_LOGE(TAG, "dns_gethostbyname() failed because: %i", res);
            }
            timestampLastFailed = espchrono::millis_clock::now();
            visualSendUdpPacket = false;
            return;
        }

        if (udpCloudIp.type != IPADDR_TYPE_V4)
        {
            ESP_LOGE(TAG, "unsupported ip type: %hhu", udpCloudIp.type);
            visualSendUdpPacket = false;
            return;
        }

        sockaddr_in receipient;
        receipient.sin_port = htons(24242);
        receipient.sin_addr.s_addr = udpCloudIp.u_addr.ip4.addr;
        receipient.sin_family = AF_INET;

        wifi_stack::UdpSender udpCloudSender;
        std::string buf = buildUdpCloudJson();


        if (const auto result = udpCloudSender.send(receipient, buf); !result)
        {
            ESP_LOGE(TAG, "send to cloud failed");
        }

        ESP_LOGD(TAG, "now: %s", buf.c_str());
        visualSendUdpPacket = !visualSendUdpPacket;
        }
}
#endif
