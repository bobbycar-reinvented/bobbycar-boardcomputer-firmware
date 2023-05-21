#include "espnowsettingsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <textinterface.h>
#include <textwithvaluehelper.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "guihelpers/bobbycheckbox.h"

namespace bobby {

namespace {
constexpr char TEXT_ESPNOW_SETTINGS[] = "ESP-Now settings";
constexpr char TEXT_ESPNOW_SYNCTIME[] = "Sync time (no NTP)";
constexpr char TEXT_ESPNOW_SYNCWITHOTHERS[] = "Sync time with others";
constexpr char TEXT_ESPNOW_SYNCBLINK[] = "Sync blink";
constexpr char TEXT_ESPNOW_ENABLE_CLOUD[] = "Enable cloud";
constexpr char TEXT_ESPNOW_CLOUD_SENDRATE[] = "Send rate";
constexpr char TEXT_BACK[] = "Back";

using ESPNowSendRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticTitle<TEXT_ESPNOW_CLOUD_SENDRATE>,
    ESPNowCloudSendRateAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

EspNowSettingsMenu::EspNowSettingsMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCTIME>, BobbyCheckbox, ESPNowSyncTimeEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCWITHOTHERS>, BobbyCheckbox, ESPNowSyncTimeWithOthersEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCBLINK>, BobbyCheckbox, ESPNowSyncBlinkEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_ENABLE_CLOUD>, BobbyCheckbox, ESPNowCloudEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ESPNOW_CLOUD_SENDRATE, ESPNowCloudSendRateAccessor>, PushScreenAction<ESPNowSendRateChangeDisplay>>>();
}

std::string EspNowSettingsMenu::title() const
{
    return TEXT_ESPNOW_SETTINGS;
}

void EspNowSettingsMenu::back()
{
    espgui::popScreen();
}

} // namespace bobby
