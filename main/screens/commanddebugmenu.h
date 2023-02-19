#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/popscreenaction.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "texthelpers/debugtexthelpers.h"

namespace bobby::debug {

template<const char *Ttitle, typename Ttexts>
class CommandDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticTitle<Ttitle>,
    public espgui::BackActionInterface<espgui::PopScreenAction>
{
public:
    CommandDebugMenu()
    {
        using namespace espgui;
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerFreqText,    DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BuzzerPatternText, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::PoweroffText,      DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::LedText,           DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
    }

private:
    static constexpr char TEXT_BACK[] = "Back";
};

constexpr char TEXT_FRONTCOMMAND[] = "Front command";
constexpr char TEXT_BACKCOMMAND[] = "Back command";
using FrontCommandDebugMenu = CommandDebugMenu<TEXT_FRONTCOMMAND, FrontTexts>;
using BackCommandDebugMenu = CommandDebugMenu<TEXT_BACKCOMMAND, BackTexts>;

} // namespace bobby::debug
