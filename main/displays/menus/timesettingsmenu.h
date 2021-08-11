#pragma once

// 3rdparty lib includes
#include <espchrono.h>
#include <fmt/core.h>

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"

// forward declares
namespace {
class SettingsMenu;
class TimeSettingsMenu;
} // namespace

namespace {
class CurrentUtcDateTime : public virtual TextInterface
{
public:
    std::string text() const override { return fmt::format("utc: {}", espchrono::toString(espchrono::toDateTime(espchrono::utc_clock::now()))); }
};

class CurrentLocalDateTime : public virtual TextInterface
{
public:
    std::string text() const override { return fmt::format("local: {}", espchrono::toString(espchrono::toDateTime(espchrono::local_clock::now()))); }
};

using TimezoneOffsetChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
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

class TimeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TIME>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    TimeSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, CurrentUtcDateTime,                  StaticFont<2>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, CurrentLocalDateTime,                StaticFont<2>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OFFSET>,             SwitchScreenAction<TimezoneOffsetChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DAYLIGHTSAVINGMODE>, SwitchScreenAction<DaylightSavingModeChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
