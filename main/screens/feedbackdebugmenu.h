#pragma once

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <menuitem.h>

// local includes
#include "debugcolorhelpers.h"
#include "guihelpers/bobbymenudisplay.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "screens/debugmenu.h"
#include "texthelpers/debugtexthelpers.h"
#include "utils.h"

namespace bobby::debug {

template<const char *Ttext, typename Ttexts, template<int> class ColorInterface>
class FeedbackDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticTitle<Ttext>,
    public espgui::BackActionInterface<espgui::PopScreenAction>
{
public:
    FeedbackDebugMenu()
    {
        using namespace espgui;
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::BatVoltageText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BatVoltageFixedText,  ColorInterface<espgui::TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::BoardTempText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::BoardTempFixedText,   ColorInterface<espgui::TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::TimeoutCntSerialText, StaticFont<2>, ColorInterface<espgui::TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
    }

private:
    static constexpr char TEXT_BACK[] = "Back";
};

constexpr char TEXT_FRONTFEEDBACK[] = "Front feedback";
using FrontFeedbackDebugMenu = FeedbackDebugMenu<TEXT_FRONTFEEDBACK, FrontTexts, FrontFeedbackColor>;

constexpr char TEXT_BACKFEEDBACK[] = "Back feedback";
using BackFeedbackDebugMenu = FeedbackDebugMenu<TEXT_BACKFEEDBACK, BackTexts, FrontFeedbackColor>;

} // namespace bobby::debug
