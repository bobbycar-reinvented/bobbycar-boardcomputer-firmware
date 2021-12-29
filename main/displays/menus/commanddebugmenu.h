#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "debugmenu.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "debugtexthelpers.h"

using namespace espgui;

namespace {
template<const char *Ttext, typename Ttexts>
class CommandDebugMenu :
    public BobbyMenuDisplay,
    public StaticText<Ttext>,
    public BackActionInterface<SwitchScreenAction<DebugMenu>>
{
public:
    CommandDebugMenu()
    {
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerFreqText,    DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerPatternText, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::PoweroffText,      DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::LedText,           DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};

using FrontCommandDebugMenu = CommandDebugMenu<TEXT_FRONTCOMMAND, FrontTexts>;
using BackCommandDebugMenu = CommandDebugMenu<TEXT_BACKCOMMAND, BackTexts>;

} // namespace
