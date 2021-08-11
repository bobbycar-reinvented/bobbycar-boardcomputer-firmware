#pragma once

// esp-idf includes
#include <esp_log.h>

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
class ChangeValueDisplay<sntp_sync_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<sntp_sync_mode_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

ChangeValueDisplay<sntp_sync_mode_t>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<sntp_sync_mode_t>, StaticText<TEXT_IMMED>>>(SNTP_SYNC_MODE_IMMED, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<sntp_sync_mode_t>, StaticText<TEXT_SMOOTH>>>(SNTP_SYNC_MODE_SMOOTH, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>>>(*this);
}

void ChangeValueDisplay<sntp_sync_mode_t>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case SNTP_SYNC_MODE_IMMED:  setSelectedIndex(0); break;
    case SNTP_SYNC_MODE_SMOOTH: setSelectedIndex(1); break;
    default:
        ESP_LOGW("BOBBY", "Unknown sntp_sync_mode_t: %i", int(value));
        setSelectedIndex(2);
    }
}
}
