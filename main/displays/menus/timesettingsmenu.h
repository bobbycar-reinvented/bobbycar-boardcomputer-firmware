#pragma once

// 3rdparty lib includes
#include <espchrono.h>
#include <fmt/core.h>

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"
#include "espstrutils.h"

// forward declares
namespace {
class SettingsMenu;
class TimeSettingsMenu;
} // namespace

namespace {
class CurrentUtcDateTimeText : public virtual TextInterface { public:
    std::string text() const override { return fmt::format("utc: {}", espchrono::toString(espchrono::toDateTime(espchrono::utc_clock::now()))); }};

class CurrentLocalDateTimeText : public virtual TextInterface { public:
    std::string text() const override { return fmt::format("local: {}", espchrono::toString(espchrono::toDateTime(espchrono::local_clock::now()))); }};

using TimezoneOffsetChangeDisplay = makeComponent<
    ChangeValueDisplay<int32_t>,
    StaticText<TEXT_OFFSET>,
    TimezoneOffsetAccessor,
    BackActionInterface<SwitchScreenAction<TimeSettingsMenu>>,
    SwitchScreenAction<TimeSettingsMenu>
>;

using DaylightSavingModeChangeDisplay = makeComponent<
    ChangeValueDisplay<espchrono::DayLightSavingMode>,
    StaticText<TEXT_DAYLIGHTSAVINGMODE>,
    DaylightSavingModeAccessor,
    BackActionInterface<SwitchScreenAction<TimeSettingsMenu>>,
    SwitchScreenAction<TimeSettingsMenu>
>;

#ifdef FEATURE_NTP
using TimeSyncModeChangeDisplay = makeComponent<
    ChangeValueDisplay<sntp_sync_mode_t>,
    StaticText<TEXT_NTPMODE>,
    TimeSyncModeAccessor,
    BackActionInterface<SwitchScreenAction<TimeSettingsMenu>>,
    SwitchScreenAction<TimeSettingsMenu>
>;

using TimeSyncIntervalChangeDisplay = makeComponent<
    ChangeValueDisplay<int32_t>,
    StaticText<TEXT_NTPINTERVAL>,
    TimeSyncIntervalAccessor,
    BackActionInterface<SwitchScreenAction<TimeSettingsMenu>>,
    SwitchScreenAction<TimeSettingsMenu>
>;

class NtpSyncStatusText : public virtual TextInterface { public:
    std::string text() const override { return fmt::format("Status: {}", espcpputils::toString(sntp_get_sync_status())); }};
#endif

class TimeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TIME>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    TimeSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, CurrentUtcDateTimeText,              StaticFont<2>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, CurrentLocalDateTimeText,            StaticFont<2>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OFFSET>,             SwitchScreenAction<TimezoneOffsetChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DAYLIGHTSAVINGMODE>, SwitchScreenAction<DaylightSavingModeChangeDisplay>>>();
#ifdef FEATURE_NTP
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPENABLED>,         ToggleBoolAction, CheckboxIcon, TimeServerEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPSERVER>,          DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPMODE>,            SwitchScreenAction<TimeSyncModeChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NTPINTERVAL>,        SwitchScreenAction<TimeSyncIntervalChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, NtpSyncStatusText,                   DummyAction>>();
#endif
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
