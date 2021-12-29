#include "wifiapsettingsmenu.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <menuitem.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <checkboxicon.h>
#include <actions/toggleboolaction.h>
#include <icons/back.h>
#include <screenmanager.h>
#include <espwifistack.h>
#include <textwithvaluehelper.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "changevaluedisplay.h"
#include "changevaluedisplay_wifi_auth_mode_t.h"
#include "wifiapclientsmenu.h"
#include "networksettingsmenu.h"
#include "accessors/wifiapconfigaccessors.h"
#include "texthelpers/wifiaptexthelpers.h"

using namespace espgui;

namespace {
constexpr const char * const TAG = "BOBBY";

constexpr char TEXT_ENABLED[] = "Enabled";
constexpr char TEXT_DISABLEWHENONLINE[] = "Disable when online";
constexpr char TEXT_BACK[] = "Back";

constexpr char TEXT_SSID[] = "AP SSID";
constexpr char TEXT_SSID_FORMATTED[] = "&sssid: &2";
constexpr char TEXT_KEY[] = "AP Key";
constexpr char TEXT_KEY_FORMATTED[] = "&skey: &2";
constexpr char TEXT_IP[] = "AP IP";
constexpr char TEXT_IP_FORMATTED[] = "&sIP: &f&2";
constexpr char TEXT_MASK[] = "AP Mask";
constexpr char TEXT_MASK_FORMATTED[] = "&sMask: &f&2";
constexpr char TEXT_CHANNEL[] = "AP Channel";
constexpr char TEXT_CHANNEL_FORMATTED[] = "&sChannel: &f&2";
constexpr char TEXT_AUTHMODE[] = "AP Authmode";
constexpr char TEXT_AUTHMODE_FORMATTED[] = "&sAuthmode: &2";

class WifiApClientsAction : public virtual ActionInterface
{
public:
    void triggered() override;
};

using ApChannelChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_CHANNEL>,
    WifiApChannelAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<WifiApSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<WifiApSettingsMenu>>
>;

using ApAuthmodeChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<wifi_auth_mode_t>,
    espgui::StaticText<TEXT_AUTHMODE>,
    WifiApAuthmodeAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<WifiApSettingsMenu>>,
    espgui::SwitchScreenAction<WifiApSettingsMenu>
>;
} // namespace

WifiApSettingsMenu::WifiApSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLED>,            ToggleBoolAction, CheckboxIcon, WifiApEnabledAccessor>>();
    //constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISABLEWHENONLINE>,  ToggleBoolAction, CheckboxIcon, WifiApDisableWhenOnlineAccessor>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SSID_FORMATTED, WifiApNameAccessor>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_KEY_FORMATTED, WifiApKeyAccessor>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApMacText,                       DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_IP_FORMATTED, WifiApIpAccessor>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_MASK_FORMATTED, WifiApMaskAccessor>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CHANNEL_FORMATTED, WifiApChannelAccessor>, SwitchScreenAction<ApChannelChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_AUTHMODE_FORMATTED, WifiApAuthmodeAccessor>, SwitchScreenAction<ApAuthmodeChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, WifiApHostnameText,                  DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApClientsText,                   WifiApClientsAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<NetworkSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
}

std::string WifiApSettingsMenu::text() const
{
    return "AP Settings";
}

void WifiApSettingsMenu::back()
{
    switchScreen<NetworkSettingsMenu>();
}

namespace {
void WifiApClientsAction::triggered()
{
    wifi_sta_list_t clients;
    if (const auto result = esp_wifi_ap_get_sta_list(&clients); result == ESP_OK)
        switchScreen<WifiApClientsMenu>();
    else
        ESP_LOGW(TAG, "esp_wifi_ap_get_sta_list() failed with %s", esp_err_to_name(result));
}
} // namespace
