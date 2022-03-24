#include "bobbyhupe.h"

// system includes
#include <esp_log.h>

// local includes
#include "espnowfunctions.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "BOBBY_HUPE";

void sendState(const std::string& state)
{
    if (const auto error = espnow::send_espnow_message(fmt::format("{}:0:0", state)); error != ESP_OK)
    {
        ESP_LOGE(TAG, "Error sending hupe message: %s", esp_err_to_name(error));
    }
}
} // namespace

namespace bobbyhupe {
bool hupe_state{false};
std::optional<espchrono::millis_clock::time_point> hupe_last_time_sent;

void activate_hupe()
{
    hupe_state = true;
}

void deactivate_hupe()
{
    hupe_state = false;
}

void activate_compressor()
{
    sendState("COMPRESSOR_AN");
}

void deactivate_compressor()
{
    sendState("COMPRESSOR_AUS");
}

void toggle_compressor()
{
    sendState("COMPRESSOR_TOGGLE");
}

void handle_hupe()
{
    if ((hupe_state && !hupe_last_time_sent) || (hupe_state && hupe_last_time_sent && espchrono::ago(*hupe_last_time_sent) > 1s))
    {
        hupe_last_time_sent = espchrono::millis_clock::now();
        sendState("BOBBYHUP_AN");
    }
    else if (!hupe_state && hupe_last_time_sent)
    {
        hupe_last_time_sent = std::nullopt;
        sendState("BOBBYHUPE_AUS");
    }
}
} // namespace bobbyhupe
