#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "unifiedmodelmode.h"

namespace {
template<>
class ChangeValueDisplay<UnifiedModelMode> :
    public MenuDisplay,
    public virtual AccessorInterface<UnifiedModelMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    std::size_t size() const override { return 6; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_commutationItem;
        case 1: return m_sinusoidalItem;
        case 2: return m_focVoltageItem;
        case 3: return m_focSpeedItem;
        case 4: return m_focTorqueItem;
        case 5: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_commutationItem;
        case 1: return m_sinusoidalItem;
        case 2: return m_focVoltageItem;
        case 3: return m_focSpeedItem;
        case 4: return m_focTorqueItem;
        case 5: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_commutationItem);
        callback(m_sinusoidalItem);
        callback(m_focVoltageItem);
        callback(m_focSpeedItem);
        callback(m_focTorqueItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_commutationItem);
        callback(m_sinusoidalItem);
        callback(m_focVoltageItem);
        callback(m_focSpeedItem);
        callback(m_focTorqueItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<UnifiedModelMode>, StaticText<TEXT_COMMUTATION>> m_commutationItem{UnifiedModelMode::Commutation, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<UnifiedModelMode>, StaticText<TEXT_SINUSOIDAL>> m_sinusoidalItem{UnifiedModelMode::Sinusoidal, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<UnifiedModelMode>, StaticText<TEXT_FOCVOLTAGE>> m_focVoltageItem{UnifiedModelMode::FocVoltage, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<UnifiedModelMode>, StaticText<TEXT_FOCSPEED>> m_focSpeedItem{UnifiedModelMode::FocSpeed, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<UnifiedModelMode>, StaticText<TEXT_FOCTORQUE>> m_focTorqueItem{UnifiedModelMode::FocTorque, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<UnifiedModelMode>::start()
{
    Base::start();

    if (getValue() == m_commutationItem.value()) setSelectedIndex(0); else
    if (getValue() == m_sinusoidalItem.value())  setSelectedIndex(1); else
    if (getValue() == m_focVoltageItem.value())  setSelectedIndex(2); else
    if (getValue() == m_focSpeedItem.value())    setSelectedIndex(3); else
    if (getValue() == m_focTorqueItem.value())   setSelectedIndex(4); else
    {
        Serial.printf("Unknown UnifiedModelMode: %i", int(getValue()));
        setSelectedIndex(5);
    }
}
}
