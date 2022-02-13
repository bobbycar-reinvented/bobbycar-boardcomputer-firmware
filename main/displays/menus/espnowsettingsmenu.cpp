#include "espnowsettingsmenu.h"

// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include <accessorinterface.h>
#include <actioninterface.h>
#include <espchrono.h>
#include <fmt/core.h>
#include <menudisplay.h>
#include <textinterface.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "icons/time.h"
#include "espnowmenu.h"
#include "bobbycheckbox.h"
#include "espnowfunctions.h"

namespace {
constexpr char TEXT_ESPNOW_SETTINGS[] = "ESP-Now settings";
constexpr char TEXT_ESPNOW_SYNCTIME[] = "Sync time (no NTP)";
constexpr char TEXT_ESPNOW_SYNCWITHOTHERS[] = "Sync time with others";
constexpr char TEXT_ESPNOW_SYNCBLINK[] = "Sync blink";
constexpr char TEXT_BACK[] = "Back";
} // namespace

EspNowSettingsMenu::EspNowSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCTIME>, BobbyCheckbox, ESPNowSyncTimeEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCWITHOTHERS>, BobbyCheckbox, ESPNowSyncTimeWithOthersEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCBLINK>, BobbyCheckbox, ESPNowSyncBlinkEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<EspNowMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string EspNowSettingsMenu::text() const
{
    return TEXT_ESPNOW_SETTINGS;
}

void EspNowSettingsMenu::back()
{
    espgui::switchScreen<EspNowMenu>();
}
