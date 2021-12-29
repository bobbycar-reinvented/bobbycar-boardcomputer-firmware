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
#include "debugcolorhelpers.h"
#include "displays/menus/debugmenu.h"

template<const char *Ttext, typename Ttexts, template<int> class ColorInterface>
class FeedbackDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<Ttext>,
    public espgui::BackActionInterface<espgui::SwitchScreenAction<DebugMenu>>
{
public:
    FeedbackDebugMenu()
    {
        using namespace espgui;
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::BatVoltageText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BatVoltageFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::BoardTempText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BoardTempFixedText,   ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::TimeoutCntSerialText, StaticFont<2>, ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};

constexpr char TEXT_FRONTFEEDBACK[] = "Front feedback";
using FrontFeedbackDebugMenu = FeedbackDebugMenu<TEXT_FRONTFEEDBACK, FrontTexts, FrontFeedbackColor>;

constexpr char TEXT_BACKFEEDBACK[] = "Back feedback";
using BackFeedbackDebugMenu = FeedbackDebugMenu<TEXT_BACKFEEDBACK, BackTexts, FrontFeedbackColor>;
