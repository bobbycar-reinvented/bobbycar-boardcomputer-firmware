#include "cloudsettingsmenu.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include "menuitem.h"
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "cloudtexthelpers.h"
#include "accessors/settingsaccessors.h"
#include "cloud.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

#ifdef FEATURE_CLOUD
namespace {

using CloudTransmitTimeoutChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CLOUDTRANSMITTIMEOUT>,
    CloudTransmitTimeoutAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>
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
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>
>;

using CloudSendRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CLOUDSENDRATE>,
    CloudSendRateAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<CloudSettingsMenu>>
>;
} // namespace

using namespace espgui;

CloudSettingsMenu::CloudSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDENABLED>,         BobbyCheckbox, CloudEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDTRANSMITTIMEOUT>, SwitchScreenAction<CloudTransmitTimeoutChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, CloudCreatedText,                      DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudStartedText,                      DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudConnectedText,                    DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CloudBufferLengthText,                 DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDCOLLECTRATE>,     SwitchScreenAction<CloudCollectRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDSENDRATE>,        SwitchScreenAction<CloudSendRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void CloudSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
