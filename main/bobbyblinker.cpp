#include "bobbyblinker.h"

// system includes
#include <esp_log.h>

// 3rdparty lib includes
#include <cpputils.h>

// local includes
#include "globals.h"
#include "espnowfunctions.h"
#include "ledstrip.h"

using namespace std::chrono_literals;

namespace {
    constexpr const char * const TAG = "BOBBY_BLINKER";

    void sendState(const std::string& state)
    {
        if (const auto error = espnow::send_espnow_message(fmt::format("{}:{}:{}", state, espchrono::utc_clock::now().time_since_epoch().count(), configs.anhaenger_id.value)); error != ESP_OK)
        {
            ESP_LOGE(TAG, "Error sending blinker message: %s", esp_err_to_name(error));
        }
    }

    bool brakeLightsOffSent{false};
} // namespace

namespace bobbyblinker {
    std::optional<espchrono::millis_clock::time_point> blinker_last_time_sent;
    std::optional<espchrono::millis_clock::time_point> brake_last_time_sent;

    void handle_blinker()
    {
        if (!configs.espnow.syncBlink.value)
            return;

        const bool blinker_state = (cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH));
        if ((blinker_state && !blinker_last_time_sent) || (blinker_state && blinker_last_time_sent && espchrono::ago(*blinker_last_time_sent) > 500ms))
        {
            blinker_last_time_sent = espchrono::millis_clock::now();
            if (blinkAnimation == LEDSTRIP_OVERWRITE_BLINKLEFT)
            {
                sendState("BLINKLEFT");
            }
            else if (blinkAnimation == LEDSTRIP_OVERWRITE_BLINKRIGHT)
            {
                sendState("BLINKRIGHT");
            }
            else if (blinkAnimation == LEDSTRIP_OVERWRITE_BLINKBOTH)
            {
                sendState("BLINKBOTH");
            }
        }
        else if (!blinker_state && blinker_last_time_sent)
        {
            blinker_last_time_sent = std::nullopt;
            sendState("BLINKOFF");
        }
        if (configs.ledstrip.enableBrakeLights.value && espchrono::ago(*brake_last_time_sent) > 500ms)
        {
            float avgPwm{};
            for (const Controller &controller: controllers) {
                avgPwm +=
                        controller.command.left.pwm * (controller.invertLeft ? -1 : 1) +
                        controller.command.right.pwm * (controller.invertRight ? -1 : 1);
            }
            avgPwm /= 4;

            if (avgPwm < -1.f)
            {
                sendState("BRAKELIGHTSON");
                brakeLightsOffSent = false;
            }
            else if (!brakeLightsOffSent && avgPwm > -1.f)
            {
                sendState("BRAKELIGHTSOFF");
                brakeLightsOffSent = true;
            }
        }
    }
} // namespace bobbyblinker
