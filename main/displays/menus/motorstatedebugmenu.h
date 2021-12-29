#pragma once

// 3rdparty lib includes
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbymenudisplay.h"
#include "debugmenu.h"
#include "utils.h"
#include "texts.h"
#include "debugtexthelpers.h"

template<const char *Ttext, typename Ttexts>
class MotorStateDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<Ttext>,
    public espgui::BackActionInterface<espgui::SwitchScreenAction<DebugMenu>>
{
public:
    MotorStateDebugMenu()
    {
        using namespace espgui;
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::EnableText,        DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::PwmText,           DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::CtrlTypText,       DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::CtrlModText,       DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::IMotMaxText,       DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::IDcMaxText,        DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::NMotMaxText,       DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::FieldWeakMaxText,  DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::PhaseAdvMaxText,   DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::CruiseCtrlEnaText, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::NCruiseMotTgtText, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,    SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};

using FrontLeftMotorStateDebugMenu = MotorStateDebugMenu<TEXT_FRONTLEFTCOMMAND, FrontTexts::LeftCommand>;
using FrontRightMotorStateDebugMenu = MotorStateDebugMenu<TEXT_FRONTRIGHTCOMMAND, FrontTexts::RightCommand>;
using BackLeftMotorStateDebugMenu = MotorStateDebugMenu<TEXT_BACKLEFTCOMMAND, BackTexts::LeftCommand>;
using BackRightMotorStateDebugMenu = MotorStateDebugMenu<TEXT_BACKRIGHTCOMMAND, BackTexts::RightCommand>;
