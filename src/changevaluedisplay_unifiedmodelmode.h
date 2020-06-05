#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "unifiedmodelmode.h"

namespace {
template<>
class ChangeValueDisplay<UnifiedModelMode> :
    public MenuDisplay,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_COMMUTATION>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SINUSOIDAL>,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FOCVOLTAGE>,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FOCSPEED>,    DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FOCTORQUE>,   DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,        DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<UnifiedModelMode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    void itemPressed(int index) override;
};

void ChangeValueDisplay<UnifiedModelMode>::start()
{
    Base::start();

    if (getValue() == UnifiedModelMode::Commutation)
        setSelectedIndex(0);
    else if (getValue() == UnifiedModelMode::Sinusoidal)
        setSelectedIndex(1);
    else if (getValue() == UnifiedModelMode::FocVoltage)
        setSelectedIndex(2);
    else if (getValue() == UnifiedModelMode::FocSpeed)
        setSelectedIndex(3);
    else if (getValue() == UnifiedModelMode::FocTorque)
        setSelectedIndex(4);
    else
    {
        Serial.printf("Unknown UnifiedModelMode: %i", int(getValue()));
        setSelectedIndex(5);
    }
}

void ChangeValueDisplay<UnifiedModelMode>::itemPressed(int index)
{
    switch (index)
    {
    case 0: setValue(UnifiedModelMode::Commutation); break;
    case 1: setValue(UnifiedModelMode::Sinusoidal); break;
    case 2: setValue(UnifiedModelMode::FocVoltage); break;
    case 3: setValue(UnifiedModelMode::FocSpeed); break;
    case 4: setValue(UnifiedModelMode::FocTorque); break;
    }

    triggered();
}
}
