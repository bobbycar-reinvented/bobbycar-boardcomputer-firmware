#include "cloudsettingsmenu.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include "menuitem.h"
#include "changevaluedisplay.h"
#include "actions/pushscreenaction.h"
#include "actions/popscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "bobbycheckbox.h"
#include "cloud.h"
#include "cloudtexthelpers.h"
#include "displays/bobbychangevaluedisplay.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/typesafeenumchangemenu.h"

namespace {
constexpr char TEXT_CLOUDSETTINGS[] = "Cloud settings";
constexpr char TEXT_CLOUDENABLED[] = "Cloud enabled";
constexpr char TEXT_CLOUDTRANSMITTIMEOUT[] = "Transmit timeout";
constexpr char TEXT_SENDSTATISTICS[] = "Send Statistics";
constexpr char TEXT_CLOUDCOLLECTRATE[] = "Cloud collect rate";
constexpr char TEXT_CLOUDSENDRATE[] = "Cloud send rate";
constexpr char TEXT_BACK[] = "Back";

using CloudTransmitTimeoutChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CLOUDTRANSMITTIMEOUT>,
    CloudTransmitTimeoutAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

struct CloudBufferLengthText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("buffer: {}", cloudBuffer.size());
    }
};

using CloudCollectRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CLOUDCOLLECTRATE>,
    CloudCollectRateAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using CloudSendRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CLOUDSENDRATE>,
    CloudSendRateAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

using namespace espgui;

CloudSettingsMenu::CloudSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDENABLED>,         BobbyCheckbox, CloudEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDTRANSMITTIMEOUT>, PushScreenAction<CloudTransmitTimeoutChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SENDSTATISTICS>,       BobbyCheckbox, CloudSendStatisticsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, CloudCreatedText,                      DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudStartedText,                      DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudConnectedText,                    DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudBufferLengthText,                 DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDCOLLECTRATE>,     PushScreenAction<CloudCollectRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDSENDRATE>,        PushScreenAction<CloudSendRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 PushScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string CloudSettingsMenu::text() const
{
    return TEXT_CLOUDSETTINGS;
}

void CloudSettingsMenu::back()
{
    popScreen();
}
