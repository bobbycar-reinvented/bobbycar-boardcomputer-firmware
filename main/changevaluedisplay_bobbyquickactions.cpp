#include "changevaluedisplay_bobbyquickactions.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <actions/setvalueaction.h>
#include <actions/backproxyaction.h>
#include <icons/back.h>
#include <futurecpp.h>

// local includes
#include "utils.h"

namespace espgui {
namespace {
constexpr const char * const TAG = "ESPGUI";

constexpr char TEXT_QUICKACTION_NONE[] = "None";
constexpr char TEXT_QUICKACTION_BLINK_LEFT[] = "Blink Left";
constexpr char TEXT_QUICKACTION_BLINK_RIGHT[] = "Blink Right";
constexpr char TEXT_QUICKACTION_HANDBREMSE[] = "Handbremse";
constexpr char TEXT_QUICKACTION_OPEN_GARAGE[] = "Open Garage";
constexpr char TEXT_QUICKACTION_WIFI_SCAN[] = "Wifi Scan";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ChangeValueDisplay<BobbyQuickActions>::ChangeValueDisplay()
{
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_NONE>>>(BobbyQuickActions::NONE, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_BLINK_LEFT>>>(BobbyQuickActions::BLINK_LEFT, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_BLINK_RIGHT>>>(BobbyQuickActions::BLINK_RIGHT, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_HANDBREMSE>>>(BobbyQuickActions::HANDBREMSE, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_OPEN_GARAGE>>>(BobbyQuickActions::OPEN_GARAGE, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, SetValueAction<BobbyQuickActions>, StaticText<TEXT_QUICKACTION_WIFI_SCAN>>>(BobbyQuickActions::WIFI_SCAN, *this, *this, *this);
    constructMenuItem<makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&espgui::icons::back>>>(*this);
}

void ChangeValueDisplay<BobbyQuickActions>::start()
{
    Base::start();

    switch (const auto value = getValue())
    {
    case BobbyQuickActions::NONE: setSelectedIndex(0); break;
    case BobbyQuickActions::BLINK_LEFT: setSelectedIndex(1); break;
    case BobbyQuickActions::BLINK_RIGHT: setSelectedIndex(2); break;
    case BobbyQuickActions::HANDBREMSE: setSelectedIndex(3); break;
    case BobbyQuickActions::OPEN_GARAGE: setSelectedIndex(4); break;
    case BobbyQuickActions::WIFI_SCAN: setSelectedIndex(5); break;
    default:
        ESP_LOGW(TAG, "Unknown BobbyQuickActions: %i", std::to_underlying(value));
        setSelectedIndex(6);
    }
}

} // namespace espgui
