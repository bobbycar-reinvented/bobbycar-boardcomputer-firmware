#include "udpcloudsettingsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <changevaluedisplay_string.h>
#include <fmt/core.h>
#include <menuitem.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "guihelpers/bobbycheckbox.h"
#include "icons/back.h"
#include "icons/back_grey.h"

namespace bobby {

namespace {
constexpr char TEXT_UDPCLOUDSETTINGS[] = "UDP Cloud settings";
constexpr char TEXT_UDPCLOUDENABLED[] = "Udp Cloud enabled";
constexpr char TEXT_UDPSENDRATE[] = "Udp send rate";
constexpr char TEXT_UDPHOST[] = "Udp host";
constexpr char TEXT_UDPPORT[] = "Udp port";
constexpr char TEXT_UDPTOKEN[] = "Udp token";
constexpr char TEXT_BACK[] = "Back";

using UdpCloudSendRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticTitle<TEXT_UDPSENDRATE>,
    UdpCloudSendIntervalAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using UdpCloudHostChangeDisplay = espgui::makeComponent<
        BobbyChangeValueDisplay<std::string>,
        espgui::StaticTitle<TEXT_UDPHOST>,
        UdpCloudHostAccessor,
        espgui::ConfirmActionInterface<espgui::PopScreenAction>,
        espgui::BackActionInterface<espgui::PopScreenAction>
>;

using UdpCloudPortChangeDisplay = espgui::makeComponent<
        BobbyChangeValueDisplay<uint16_t>,
        espgui::StaticTitle<TEXT_UDPPORT>,
        UdpCloudPortAccessor,
        espgui::ConfirmActionInterface<espgui::PopScreenAction>,
        espgui::BackActionInterface<espgui::PopScreenAction>
>;

using UdpCloudTokenChangeDisplay = espgui::makeComponent<
        BobbyChangeValueDisplay<std::string>,
        espgui::StaticTitle<TEXT_UDPTOKEN>,
        UdpCloudTokenAccessor,
        espgui::ConfirmActionInterface<espgui::PopScreenAction>,
        espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

using namespace espgui;

UdpCloudSettingsMenu::UdpCloudSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPCLOUDENABLED>,      BobbyCheckbox, UdpCloudEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPSENDRATE>,          PushScreenAction<UdpCloudSendRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPHOST>,              PushScreenAction<UdpCloudHostChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPPORT>,              PushScreenAction<UdpCloudPortChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPTOKEN>,             PushScreenAction<UdpCloudTokenChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string UdpCloudSettingsMenu::title() const
{
    return TEXT_UDPCLOUDSETTINGS;
}

void UdpCloudSettingsMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
