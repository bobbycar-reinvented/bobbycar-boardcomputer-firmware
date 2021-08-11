#pragma once

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<espchrono::DayLightSavingMode> :
    public MenuDisplay,
    public virtual AccessorInterface<espchrono::DayLightSavingMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

ChangeValueDisplay<espchrono::DayLightSavingMode>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_NONE>>>(espchrono::DayLightSavingMode::None, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_EUROPEANSUMMERTIME>>>(espchrono::DayLightSavingMode::EuropeanSummerTime, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<espchrono::DayLightSavingMode>, StaticText<TEXT_USDAYLIGHTTIME>>>(espchrono::DayLightSavingMode::UsDaylightTime, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>>>(*this);
}

void ChangeValueDisplay<espchrono::DayLightSavingMode>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case espchrono::DayLightSavingMode::None:               setSelectedIndex(0); break;
    case espchrono::DayLightSavingMode::EuropeanSummerTime: setSelectedIndex(1); break;
    case espchrono::DayLightSavingMode::UsDaylightTime:     setSelectedIndex(2); break;
    default:
        ESP_LOGW("BOBBY", "Unknown DayLightSavingMode: %i", int(value));
        setSelectedIndex(3);
    }
}
}
