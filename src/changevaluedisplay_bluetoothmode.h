#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "bluetoothmode.h"

namespace {
template<>
class ChangeValueDisplay<BluetoothMode> :
    public MenuDisplay,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_OFF>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_MASTER>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SLAVE>,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,   DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<BluetoothMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    void itemPressed(int index) override;
};

void ChangeValueDisplay<BluetoothMode>::start()
{
    Base::start();

    if (getValue() == BluetoothMode::Off)
        setSelectedIndex(0);
    else if (getValue() == BluetoothMode::Master)
        setSelectedIndex(1);
    else if (getValue() == BluetoothMode::Slave)
        setSelectedIndex(2);
    else
    {
        Serial.printf("Unknown BluetoothMode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}

void ChangeValueDisplay<BluetoothMode>::itemPressed(int index)
{
    switch (index)
    {
    case 0: setValue(BluetoothMode::Off); break;
    case 1: setValue(BluetoothMode::Master); break;
    case 2: setValue(BluetoothMode::Slave); break;
    }

    triggered();
}
}
