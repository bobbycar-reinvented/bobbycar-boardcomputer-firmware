#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/multiaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "modes/larsmmode.h"

namespace {
class MainMenu;
}

namespace {
template<typename T1, T1 &target, typename T2, T2 value>
class SetterAction : public ActionInterface
{
public:
    void triggered() override { target = value; }
};
using SetDefaultModeAction = SetterAction<ModeInterface*, currentMode, DefaultMode*, &modes::defaultMode>;
using SetTempomatModeAction = SetterAction<ModeInterface*, currentMode, TempomatMode*, &modes::tempomatMode>;
using SetLarsmModeAction = SetterAction<ModeInterface*, currentMode, LarsmMode*, &modes::larsmMode>;

class SelectModeMenu :
    public MenuDisplay,
    public StaticText<TEXT_SELECTMODE>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULT>,   MultiAction<SetDefaultModeAction, SwitchScreenAction<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMAT>,  MultiAction<SetTempomatModeAction, SwitchScreenAction<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSM>,     MultiAction<SetLarsmModeAction, SwitchScreenAction<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,      SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{
    using Base = MenuDisplay;

public:
    void start() override;
};

void SelectModeMenu::start()
{
    Base::start();

    if (currentMode == &modes::defaultMode)
        setSelectedIndex(0);
    else if (currentMode == &modes::tempomatMode)
        setSelectedIndex(1);
    else if (currentMode == &modes::larsmMode)
        setSelectedIndex(2);
    else
    {
        Serial.printf("Unknown mode: %s", currentMode?currentMode->displayName():"");
        setSelectedIndex(3);
    }
}
}
