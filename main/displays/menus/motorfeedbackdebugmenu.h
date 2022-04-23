#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/popscreenaction.h"
#include "icons/back.h"
#include "debugtexthelpers.h"
#include "debugcolorhelpers.h"

template<const char *Ttext, typename Ttexts, template<int> class ColorInterface>
class MotorFeedbackDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<Ttext>,
    public espgui::BackActionInterface<espgui::PopScreenAction>
{
public:
    MotorFeedbackDebugMenu()
    {
        using namespace espgui;

        constructMenuItem<makeComponent<MenuItem, typename Ttexts::AngleText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::SpeedText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::SpeedKmhText,     ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::ErrorText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcLinkText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcLinkFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaAText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaAFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaBText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaBFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        //constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaCText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::DcPhaCFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::ChopsText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, typename Ttexts::HallText,         ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             PopScreenAction, StaticMenuItemIcon<&espgui::icons::back>>>();
    }

private:
    static constexpr char TEXT_BACK[] = "Back";
};

constexpr char TEXT_FRONTLEFTFEEDBACK[] = "Front left feedback";
using FrontLeftMotorFeedbackDebugMenu = MotorFeedbackDebugMenu<TEXT_FRONTLEFTFEEDBACK, FrontTexts::LeftFeedback, FrontFeedbackColor>;

constexpr char TEXT_FRONTRIGHTFEEDBACK[] = "Front right feedback";
using FrontRightMotorFeedbackDebugMenu = MotorFeedbackDebugMenu<TEXT_FRONTRIGHTFEEDBACK, FrontTexts::RightFeedback, FrontFeedbackColor>;

constexpr char TEXT_BACKLEFTFEEDBACK[] = "Back left feedback";
using BackLeftMotorFeedbackDebugMenu = MotorFeedbackDebugMenu<TEXT_BACKLEFTFEEDBACK, BackTexts::LeftFeedback, BackFeedbackColor>;

constexpr char TEXT_BACKRIGHTFEEDBACK[] = "Back right feedback";
using BackRightMotorFeedbackDebugMenu = MotorFeedbackDebugMenu<TEXT_BACKRIGHTFEEDBACK, BackTexts::RightFeedback, BackFeedbackColor>;
