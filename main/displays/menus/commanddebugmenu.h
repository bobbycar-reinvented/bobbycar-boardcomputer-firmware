#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "debugmenu.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "debugtexthelpers.h"

template<const char *Ttext, typename Ttexts>
class CommandDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<Ttext>,
    public espgui::BackActionInterface<espgui::SwitchScreenAction<DebugMenu>>
{
public:
    CommandDebugMenu()
    {
        using namespace espgui;
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerFreqText,    DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerPatternText, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::PoweroffText,      DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::LedText,           DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }

private:
    static constexpr char TEXT_BACK[] = "Back";
};

constexpr char TEXT_FRONTCOMMAND[] = "Front command";
constexpr char TEXT_BACKCOMMAND[] = "Back command";
using FrontCommandDebugMenu = CommandDebugMenu<TEXT_FRONTCOMMAND, FrontTexts>;
using BackCommandDebugMenu = CommandDebugMenu<TEXT_BACKCOMMAND, BackTexts>;
