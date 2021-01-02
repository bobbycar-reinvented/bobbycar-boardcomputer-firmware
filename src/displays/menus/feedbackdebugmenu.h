#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "debugtexthelpers.h"
#include "debugcolorhelpers.h"

// forward declares
namespace {
class DebugMenu;
} // namespace

namespace {
template<const char *Ttext, typename Ttexts, template<int> class ColorInterface>
class FeedbackDebugMenu :
    public MenuDisplay,
    public StaticText<Ttext>,
    public BackActionInterface<SwitchScreenAction<DebugMenu>>,
    public ContainerMenuDefinition
{
public:
    FeedbackDebugMenu()
    {
        constructItem<makeComponent<MenuItem, typename Ttexts::BatVoltageText,       ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructItem<makeComponent<MenuItem, typename Ttexts::BatVoltageFixedText,  ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructItem<makeComponent<MenuItem, typename Ttexts::BoardTempText,        ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructItem<makeComponent<MenuItem, typename Ttexts::BoardTempFixedText,   ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructItem<makeComponent<MenuItem, typename Ttexts::TimeoutCntSerialText, StaticFont<2>, ColorInterface<TFT_DARKGREY>, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};

class FrontFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_FRONTFEEDBACK, FrontTexts, FrontFeedbackColor> {};
class BackFeedbackDebugMenu : public FeedbackDebugMenu<TEXT_BACKFEEDBACK, BackTexts, FrontFeedbackColor> {};

} // namespace
