#include "tempomatmodesettingsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <changevaluedisplay.h>
#include <menuitem.h>
#include <textwithvaluehelper.h>

// local includes
#include "accessors/globalaccessors.h"
#include "accessors/settingsaccessors.h"
#include "actions/tempomatmodeapplycurrentpeedaction.h"
#include "changevaluedisplay_unifiedmodelmode.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "utils.h"

namespace bobby {

namespace {
constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
constexpr char TEXT_APPLY[] = "Apply";
constexpr char TEXT_NCRUISEMOTTGT[] = "nCruiseMotTgt";
constexpr char TEXT_MODELMODE[] = "Model mode";
constexpr char TEXT_BACK[] = "Back";

using TempomatModeCruiseMotTgtChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticTitle<TEXT_NCRUISEMOTTGT>,
    TempomatModeCruiseMotTgtAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using TempomatModeModelModeChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticTitle<TEXT_MODELMODE>,
    TempomatModeModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

using namespace espgui;

TempomatModeSettingsMenu::TempomatModeSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_APPLY, AvgSpeedAccessor>, TempomatModeApplyCurrentSpeedAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_NCRUISEMOTTGT, TempomatModeCruiseMotTgtAccessor>, PushScreenAction<TempomatModeModelModeChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>, PushScreenAction<TempomatModeModelModeChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,      PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string TempomatModeSettingsMenu::title() const
{
    return TEXT_TEMPOMATMODESETTINGS;
}

void TempomatModeSettingsMenu::back()
{
    popScreen();
}
} // namespace bobby
