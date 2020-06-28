#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
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
    void start() override;

    std::size_t size() const override { return 4; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_commutationItem;
        case 1: return m_sinusoidalItem;
        case 2: return m_fieldOrientedControlItem;
        case 3: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_commutationItem;
        case 1: return m_sinusoidalItem;
        case 2: return m_fieldOrientedControlItem;
        case 3: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_commutationItem);
        callback(m_sinusoidalItem);
        callback(m_fieldOrientedControlItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_commutationItem);
        callback(m_sinusoidalItem);
        callback(m_fieldOrientedControlItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_COMMUTATION>> m_commutationItem{ControlType::Commutation, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_SINUSOIDAL>> m_sinusoidalItem{ControlType::Sinusoidal, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<ControlType>, StaticText<TEXT_FIELDORIENTEDCONTROL>> m_fieldOrientedControlItem{ControlType::FieldOrientedControl, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<ControlType>::start()
{
    Base::start();

    if (getValue() == m_commutationItem.value())          setSelectedIndex(0); else
    if (getValue() == m_sinusoidalItem.value())           setSelectedIndex(1); else
    if (getValue() == m_fieldOrientedControlItem.value()) setSelectedIndex(2); else
    {
        Serial.printf("Unknown ControlType: %i", int(getValue()));
        setSelectedIndex(3);
    }
}
}
