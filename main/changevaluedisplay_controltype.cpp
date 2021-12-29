#include "changevaluedisplay_controltype.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <actions/setvalueaction.h>
#include <actions/backproxyaction.h>
#include <icons/back.h>
#include <futurecpp.h>

// local includes
#include "utils.h"

namespace espgui {
namespace {
constexpr const char * const TAG = "ESPGUI";

constexpr char TEXT_COMMUTATION[] = "Commutation";
constexpr char TEXT_SINUSOIDAL[] = "Sinusoidal";
constexpr char TEXT_FIELDORIENTEDCONTROL[] = "Field oriented control";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<bobbycar::protocol::ControlType>::ChangeValueDisplay()
{
    using bobbycar::protocol::ControlType;
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_COMMUTATION>>>(ControlType::Commutation, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_SINUSOIDAL>>>(ControlType::Sinusoidal, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_FIELDORIENTEDCONTROL>>>(ControlType::FieldOrientedControl, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&espgui::icons::back>>>(*this);
}

void ChangeValueDisplay<bobbycar::protocol::ControlType>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    using bobbycar::protocol::ControlType;
    case ControlType::Commutation:          setSelectedIndex(0); break;
    case ControlType::Sinusoidal:           setSelectedIndex(1); break;
    case ControlType::FieldOrientedControl: setSelectedIndex(2); break;
    default:
        ESP_LOGW(TAG, "Unknown ControlType: %i", std::to_underlying(value));
        setSelectedIndex(3);
    }
}

} // namespace espgui
