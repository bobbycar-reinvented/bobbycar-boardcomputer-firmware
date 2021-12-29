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

// local includes
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

class WifiApClientsAction : public virtual ActionInterface
{
public:
    void triggered() override;
};
} // namespace

WifiApSettingsMenu::WifiApSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, WifiApNameText,                      DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApKeyText,                       DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApMacText,                       DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApIpText,                        DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApMaskText,                      DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, WifiApHostnameText,                  DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLED>,            ToggleBoolAction, CheckboxIcon, WifiApEnabledAccessor>>();
    //constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISABLEWHENONLINE>,  ToggleBoolAction, CheckboxIcon, WifiApDisableWhenOnlineAccessor>>();
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
