#include "time_bobbycar.h"

// esp-idf includes
#include <esp_log.h>
#ifdef FEATURE_NTP
#include <lwip/apps/snmp.h>
#include <esp_sntp.h>
#endif

// 3rdparty lib includes
#include <espchrono.h>
#include <espstrutils.h>

// local includes
#include "globals.h"

namespace {
constexpr const char * const TAG = "BOBBYTIME";
} // namespace

auto espchrono::local_clock::timezone() noexcept -> time_zone
{
    return time_zone{minutes32{settings.timeSettings.timezoneOffset}, settings.timeSettings.daylightSavingMode};
}

#ifdef FEATURE_NTP
void time_sync_notification_cb(struct timeval *tv);

void initTime()
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    static_assert(SNTP_MAX_SERVERS >= 1);
    sntp_setservername(0, stringSettings.timeServer.c_str());
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_set_sync_mode(settings.timeSettings.timeSyncMode);
    sntp_set_sync_interval(espchrono::milliseconds32{settings.timeSettings.timeSyncInterval}.count());
    if (settings.timeSettings.timeServerEnabled)
    {
        ESP_LOGI("BOBBY", "sntp_init() ...");
        sntp_init();
        if (!sntp_enabled())
        {
            ESP_LOGE("BOBBY", "sntp_init() failed");
        }
    }
}

void updateTime()
{
    if (bool(sntp_enabled()) != settings.timeSettings.timeServerEnabled)
    {
        if (settings.timeSettings.timeServerEnabled)
        {
            ESP_LOGD("BOBBY", "calling sntp_init()...");
            sntp_init();
            ESP_LOGI("BOBBY", "sntp_init() finished");
        }
        else
        {
            ESP_LOGD("BOBBY", "calling sntp_stop()...");
            sntp_stop();
            ESP_LOGI("BOBBY", "sntp_stop() finished");
        }
    }

    if (stringSettings.timeServer != sntp_getservername(0))
    {
        ESP_LOGD("BOBBY", "calling sntp_getservername() with %s...", stringSettings.timeServer.c_str());
        sntp_setservername(0, stringSettings.timeServer.c_str());
        ESP_LOGI("BOBBY", "sntp_getservername() finished");
    }

    if (settings.timeSettings.timeSyncMode != sntp_get_sync_mode())
    {
        ESP_LOGD("BOBBY", "calling sntp_set_sync_mode() with %s...", espcpputils::toString(settings.timeSettings.timeSyncMode).c_str());
        sntp_set_sync_mode(settings.timeSettings.timeSyncMode);
        ESP_LOGI("BOBBY", "sntp_set_sync_mode() finished");
    }

    if (settings.timeSettings.timeSyncInterval != espchrono::milliseconds32{sntp_get_sync_interval()})
    {
        ESP_LOGD("BOBBY", "calling sntp_set_sync_interval() with %s...", espchrono::toString(settings.timeSettings.timeSyncInterval).c_str());
        sntp_set_sync_interval(espchrono::milliseconds32{settings.timeSettings.timeSyncInterval}.count());
        ESP_LOGI("BOBBY", "sntp_set_sync_interval() finished");
    }
}

tl::expected<void, std::string> time_requestSync()
{
    ESP_LOGI("BOBBY", "called");
    if (!sntp_restart())
        return tl::make_unexpected("sntp_restart() failed");
    return {};
}

void time_sync_notification_cb(struct timeval *tv)
{
    if (tv)
        ESP_LOGI("BOBBY", "%ld", tv->tv_sec);
    else
        ESP_LOGI("BOBBY", "nullptr");
}
#endif
