#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"
#ifdef FEATURE_BLUETOOTH
#include "bluetoothmode.h"
#endif

namespace {
#ifdef FEATURE_BLUETOOTH
template<>
class ChangeValueDisplay<BluetoothMode> :
    public MenuDisplay,
    public virtual AccessorInterface<BluetoothMode>,
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
        case 0: return m_offAction;
        case 1: return m_masterAction;
        case 2: return m_slaveAction;
        case 3: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_offAction;
        case 1: return m_masterAction;
        case 2: return m_slaveAction;
        case 3: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_offAction);
        callback(m_masterAction);
        callback(m_slaveAction);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_offAction);
        callback(m_masterAction);
        callback(m_slaveAction);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<BluetoothMode>, StaticText<TEXT_OFF>> m_offAction{BluetoothMode::Off, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<BluetoothMode>, StaticText<TEXT_MASTER>> m_masterAction{BluetoothMode::Master, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<BluetoothMode>, StaticText<TEXT_SLAVE>> m_slaveAction{BluetoothMode::Slave, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<BluetoothMode>::start()
{
    Base::start();

    if (getValue() == m_offAction.value())    setSelectedIndex(0); else
    if (getValue() == m_masterAction.value()) setSelectedIndex(1); else
    if (getValue() == m_slaveAction.value())  setSelectedIndex(2); else
    {
        Serial.printf("Unknown BluetoothMode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}
#endif
}
