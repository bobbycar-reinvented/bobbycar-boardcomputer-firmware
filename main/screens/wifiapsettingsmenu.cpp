#include "wifiapsettingsmenu.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <espwifistack.h>
#include <menuitem.h>
#include <screenmanager.h>
#include <textwithvaluehelper.h>

// local includes
#include "accessors/wifiapconfigaccessors.h"
#include "changevaluedisplay.h"
#include "changevaluedisplay_ip_address_t.h"
#include "changevaluedisplay_string.h"
#include "changevaluedisplay_wifi_auth_mode_t.h"
#include "espnowfunctions.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "guihelpers/bobbycheckbox.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "networksettingsmenu.h"
#include "texthelpers/wifiaptexthelpers.h"
#include "wifi_bobbycar.h"
#include "wifiapclientsmenu.h"

namespace bobby {

using namespace espgui;

namespace {
constexpr const char * const TAG = "BOBBY";

constexpr char TEXT_ENABLED[] = "Enabled";
constexpr char TEXT_DISABLEWHENONLINE[] = "Disable when online";
constexpr char TEXT_BACK[] = "Back";

constexpr char TEXT_SSID[] = "AP SSID";
constexpr char TEXT_SSID_FORMATTED[] = "&sssid: ";
constexpr char TEXT_KEY[] = "AP Key";
constexpr char TEXT_KEY_FORMATTED[] = "&skey: ";
constexpr char TEXT_IP[] = "AP IP";
constexpr char TEXT_IP_FORMATTED[] = "&sIP: &f";
constexpr char TEXT_MASK[] = "AP Mask";
constexpr char TEXT_MASK_FORMATTED[] = "&sMask: &f";
constexpr char TEXT_CHANNEL[] = "AP Channel";
constexpr char TEXT_CHANNEL_FORMATTED[] = "&sChannel: &f";
constexpr char TEXT_AUTHMODE[] = "AP Authmode";
constexpr char TEXT_AUTHMODE_FORMATTED[] = "&sAuthmode: ";
constexpr char TEXT_HIDDEN[] = "AP Hidden";
constexpr char TEXT_DISABLECHANNEL[] = "Disable channel override";
constexpr char TEXT_CHANNEL_OVERRIDE_FORMATTED[] = "&sChannel Override: &f";
constexpr char TEXT_CHANNEL_OVERRIDE_CONFIRM[] = "Confirm channel override";

class WifiApClientsAction : public virtual ActionInterface
{
public:
    void triggered() override;
};

class WiFiApDisableChannelOverrideAction : public virtual ActionInterface
{
public:
    void triggered() override;
};

class WiFiApChannelOverrideAccessor : public virtual AccessorInterface<uint8_t>
{
public:
    uint8_t getValue() const override;
    setter_result_t setValue(uint8_t value) override { return {}; }
};

class WiFiApChannelOverrideConfirmAction : public virtual ActionInterface
{
public:
    void triggered() override;
};

using ApSsidChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticTitle<TEXT_SSID>,
    WifiApSsidAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using ApKeyChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticTitle<TEXT_KEY>,
    WifiApKeyAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using ApIpChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<wifi_stack::ip_address_t>,
    espgui::StaticTitle<TEXT_IP>,
    WifiApIpAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using ApMaskChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<wifi_stack::ip_address_t>,
    espgui::StaticTitle<TEXT_MASK>,
    WifiApMaskAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using ApChannelChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticTitle<TEXT_CHANNEL>,
    WifiApChannelAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using ApAuthmodeChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<wifi_auth_mode_t>,
    espgui::StaticTitle<TEXT_AUTHMODE>,
    WifiApAuthmodeAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

WifiApSettingsMenu::WifiApSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLED>,            BobbyCheckbox, WifiApEnabledAccessor>>();
  //constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISABLEWHENONLINE>,  BobbyCheckbox, WifiApDisableWhenOnlineAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HIDDEN>,             BobbyCheckbox, WiFiApHiddenAccessor>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SSID_FORMATTED, WifiApSsidAccessor>,         PushScreenAction<ApSsidChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_KEY_FORMATTED, WifiApKeyAccessor>,           PushScreenAction<ApKeyChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, WifiApMacText,                       DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_IP_FORMATTED, WifiApIpAccessor>,             PushScreenAction<ApIpChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_MASK_FORMATTED, WifiApMaskAccessor>,         PushScreenAction<ApMaskChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CHANNEL_FORMATTED, WifiApChannelAccessor>,   PushScreenAction<ApChannelChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_AUTHMODE_FORMATTED, WifiApAuthmodeAccessor>, PushScreenAction<ApAuthmodeChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, WifiApHostnameText,                                                   DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApClientsText,                                                    WifiApClientsAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISABLECHANNEL>,                                      WiFiApDisableChannelOverrideAction>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CHANNEL_OVERRIDE_FORMATTED, WiFiApChannelOverrideAccessor>, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CHANNEL_OVERRIDE_CONFIRM>,                            WiFiApChannelOverrideConfirmAction>>();

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string WifiApSettingsMenu::title() const
{
    return "AP Settings";
}

void WifiApSettingsMenu::back()
{
    popScreen();
}

namespace {
void WifiApClientsAction::triggered()
{
    wifi_sta_list_t clients;
    if (const auto result = esp_wifi_ap_get_sta_list(&clients); result == ESP_OK)
        espgui::pushScreen<WifiApClientsMenu>();
    else
        ESP_LOGW(TAG, "esp_wifi_ap_get_sta_list() failed with %s", esp_err_to_name(result));
}

void WiFiApDisableChannelOverrideAction::triggered()
{
    disable_ap_channel_override();
}

uint8_t WiFiApChannelOverrideAccessor::getValue() const
{
    const auto value = get_ap_channel_override();
    return value ? *value : 0;
}

void WiFiApChannelOverrideConfirmAction::triggered()
{
    if (const auto res = espnow::send_espnow_message("CHOK"); res != ESP_OK)
    {
        ESP_LOGW(TAG, "espnow::send_espnow_message() failed with %s", esp_err_to_name(res));
    }
}
} // namespace

} // namespace bobby
