#include "timesettingsmenu.h"

#include "sdkconfig.h"

// 3rdparty lib includes
#include <espchrono.h>
#include <fmt/core.h>
#include "changevaluedisplay.h"
#include "changevaluedisplay_daylightsavingmode.h"
#include "changevaluedisplay_sntp_sync_mode_t.h"
#include "changevaluedisplay_string.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "espstrutils.h"
#include <sunset.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "utils.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_TIME[] = "Time";
constexpr char TEXT_OFFSET[] = "Offset";
constexpr char TEXT_DAYLIGHTSAVINGMODE[] = "Daylight Saving";
constexpr char TEXT_NTPENABLED[] = "NTP Enabled";
constexpr char TEXT_NTPSERVER[] = "NTP Server";
constexpr char TEXT_NTPMODE[] = "NTP Mode";
constexpr char TEXT_NTPINTERVAL[] = "NTP Interval";
constexpr char TEXT_BACK[] = "Back";

class CurrentUtcDateTimeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("utc: {}", espchrono::toString(espchrono::toDateTime(espchrono::utc_clock::now())));
    }
};

class CurrentLocalDateTimeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
#ifdef CONFIG_ESPCHRONO_SUPPORT_DEFAULT_TIMEZONE
        return fmt::format("local: {}", espchrono::toString(espchrono::toDateTime(espchrono::local_clock::now())));
#else // Mir egal ob die lokalzeit richtig is
        return fmt::format("local: {}", espchrono::toString(espchrono::toDateTime(espchrono::utc_clock::now() + configs.timezoneOffset.value)));
#endif
    }
};

class SuntimeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        SunSet sunSet;
        sunSet.setPosition(47.076668, 15.421371, 2); // Vienna
        sunSet.setTZOffset(2);
        const auto today = toDateTime(espchrono::utc_clock::now());
        sunSet.setCurrentDate(static_cast<int>(today.date.year()), static_cast<uint>(today.date.month()), static_cast<uint>(today.date.day()));
        const auto sunrise = static_cast<int>(sunSet.calcSunrise());
        const auto sunset = static_cast<int>(sunSet.calcSunset());
        const int sunriseHour = sunrise / 60;
        const int sunriseMinute = sunrise % 60;
        const int sunsetHour = sunset / 60;
        const int sunsetMinute = sunset % 60;
        return fmt::format("sunrise: {}:{:02d} sunset: {}:{:02d}", sunriseHour, sunriseMinute, sunsetHour, sunsetMinute);
    }
};

using TimezoneOffsetChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int32_t>,
    espgui::StaticText<TEXT_OFFSET>,
    TimezoneOffsetAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>
>;

using DaylightSavingModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<espchrono::DayLightSavingMode>,
    espgui::StaticText<TEXT_DAYLIGHTSAVINGMODE>,
    DaylightSavingModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>
>;

using TimeServerChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticText<TEXT_NTPSERVER>,
    TimeServerAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>
>;

using TimeSyncModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<sntp_sync_mode_t>,
    espgui::StaticText<TEXT_NTPMODE>,
    TimeSyncModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>
>;

using TimeSyncIntervalChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int32_t>,
    espgui::StaticText<TEXT_NTPINTERVAL>,
    TimeSyncIntervalAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimeSettingsMenu>>
>;

class NtpSyncStatusText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("Status: {}", espcpputils::toString(sntp_get_sync_status()));
    }
};
} // namespace

TimeSettingsMenu::TimeSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, CurrentUtcDateTimeText,              StaticFont<2>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentLocalDateTimeText,            StaticFont<2>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, SuntimeText,                         StaticFont<2>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OFFSET>,             SwitchScreenAction<TimezoneOffsetChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DAYLIGHTSAVINGMODE>, SwitchScreenAction<DaylightSavingModeChangeDisplay>>>();
    if (configs.feature.ntp.isEnabled.value)
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPENABLED>,         BobbyCheckbox, TimeServerEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPSERVER>,          SwitchScreenAction<TimeServerChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPMODE>,            SwitchScreenAction<TimeSyncModeChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPINTERVAL>,        SwitchScreenAction<TimeSyncIntervalChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, NtpSyncStatusText,                   DummyAction>>();
    }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string TimeSettingsMenu::text() const
{
    return TEXT_TIME;
}

void TimeSettingsMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
