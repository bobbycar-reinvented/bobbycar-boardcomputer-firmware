#include "udpcloudsettingsmenu.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include "menuitem.h"
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

#ifdef FEATURE_UDPCLOUD
namespace {
using UdpCloudSendRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_UDPSENDRATE>,
    UdpCloudSendIntervalAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<UdpCloudSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<UdpCloudSettingsMenu>>
>;
} // namespace

using namespace espgui;

UdpCloudSettingsMenu::UdpCloudSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPCLOUDENABLED>,      BobbyCheckbox, UdpCloudEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPUSESTRING>,         BobbyCheckbox, UdpUseStdStringAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPSENDRATE>,          SwitchScreenAction<UdpCloudSendRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void UdpCloudSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
