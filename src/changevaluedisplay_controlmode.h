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
class ChangeValueDisplay<ControlMode> :
    public MenuDisplay,
    public virtual AccessorInterface<ControlMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    std::size_t size() const override { return 5; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_openModeItem;
        case 1: return m_voltageItem;
        case 2: return m_speedItem;
        case 3: return m_torqueItem;
        case 4: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_openModeItem;
        case 1: return m_voltageItem;
        case 2: return m_speedItem;
        case 3: return m_torqueItem;
        case 4: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_openModeItem);
        callback(m_voltageItem);
        callback(m_speedItem);
        callback(m_torqueItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_openModeItem);
        callback(m_voltageItem);
        callback(m_speedItem);
        callback(m_torqueItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<ControlMode>, StaticText<TEXT_OPENMODE>> m_openModeItem{ControlMode::OpenMode, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<ControlMode>, StaticText<TEXT_VOLTAGE>> m_voltageItem{ControlMode::Voltage, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<ControlMode>, StaticText<TEXT_SPEED>> m_speedItem{ControlMode::Speed, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<ControlMode>, StaticText<TEXT_TORQUE>> m_torqueItem{ControlMode::Torque, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem;
};

void ChangeValueDisplay<ControlMode>::start()
{
    Base::start();

    if (getValue() == m_openModeItem.value()) setSelectedIndex(0); else
    if (getValue() == m_voltageItem.value())  setSelectedIndex(1); else
    if (getValue() == m_speedItem.value())    setSelectedIndex(2); else
    if (getValue() == m_torqueItem.value())   setSelectedIndex(3); else
    {
        Serial.printf("Unknown ControlMode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}
}
