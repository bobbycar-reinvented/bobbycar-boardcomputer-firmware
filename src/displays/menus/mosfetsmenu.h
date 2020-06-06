#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "types.h"

namespace {
class MainMenu;
}

namespace {
#ifdef FEATURE_MOSFETS
template<pin_t PIN>
class GPIOAccessor : public virtual AccessorInterface<bool>
{
public:
    bool getValue() const override { return digitalRead(PIN); }
    void setValue(bool value) override { digitalWrite(PIN, value ? HIGH : LOW); }
};

using Mosfet0Accessor = GPIOAccessor<PINS_MOSFET0>;
using Mosfet1Accessor = GPIOAccessor<PINS_MOSFET1>;
using Mosfet2Accessor = GPIOAccessor<PINS_MOSFET2>;

class MosfetsMenu :
    public MenuDisplay,
    public StaticText<TEXT_MOSFETS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_MOSFET0>, ToggleBoolAction, CheckboxIcon, Mosfet0Accessor>,
        makeComponent<MenuItem, StaticText<TEXT_MOSFET1>, ToggleBoolAction, CheckboxIcon, Mosfet1Accessor>,
        makeComponent<MenuItem, StaticText<TEXT_MOSFET2>, ToggleBoolAction, CheckboxIcon, Mosfet2Accessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,    SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
#endif
}
