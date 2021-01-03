#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<ControlType> :
    public MenuDisplay,
    public virtual AccessorInterface<ControlType>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    ChangeValueDisplay();

    void start() override;
};

ChangeValueDisplay<ControlType>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_COMMUTATION>>>(ControlType::Commutation, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_SINUSOIDAL>>>(ControlType::Sinusoidal, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_FIELDORIENTEDCONTROL>>>(ControlType::FieldOrientedControl, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>>>(*this);
}

void ChangeValueDisplay<ControlType>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case ControlType::Commutation:          setSelectedIndex(0); break;
    case ControlType::Sinusoidal:           setSelectedIndex(1); break;
    case ControlType::FieldOrientedControl: setSelectedIndex(2); break;
    default:
        Serial.printf("Unknown ControlType: %i\r\n", int(value));
        setSelectedIndex(3);
    }
}
}
