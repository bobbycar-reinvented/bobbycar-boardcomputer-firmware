#include "espnowmenu.h"

#ifdef FEATURE_ESPNOW
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
#include "icons/settings.h"
#include "icons/time.h"
#include "displays/menus/espnowsettingsmenu.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"
#include "espnowfunctions.h"

namespace {
constexpr char TEXT_ESPNOW_MENU[] = "ESP-Now Menu";
constexpr char TEXT_ESPNOW_RECEIVETS[] = "Recv Ts State";
constexpr char TEXT_ESPNOW_RECEIVETSFROMBOBBY[] = "Recv BobbyTs State";
constexpr char TEXT_ESPNOW_SENDTSMSG[] = "Broadcast Time";
constexpr char TEXT_ESPNOW_SETTINGS[] = "ESP-Now settings";
constexpr char TEXT_BACK[] = "Back";

struct ReceiveTimeStampAccessor : public espgui::RefAccessor<bool>
{
    bool &getRef() const override
    {
        return espnow::receiveTimeStamp;
    }
};
struct ReceiveTsFromOtherBobbycarsAccessor : public espgui::RefAccessor<bool>
{
    bool &getRef() const override
    {
        return espnow::receiveTsFromOtherBobbycars;
    }
};

class SendBobbycarTimesyncMessageAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        const auto message = fmt::format("BOBBYT:{}", espchrono::utc_clock::now().time_since_epoch().count());
        espnow::send_espnow_message(message);
    }
};
} // namespace

EspNowMenu::EspNowMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SENDTSMSG>, SendBobbycarTimesyncMessageAction, StaticMenuItemIcon<&bobbyicons::time>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETS>, BobbyCheckbox, ReceiveTimeStampAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETSFROMBOBBY>, BobbyCheckbox, ReceiveTsFromOtherBobbycarsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SETTINGS>, SwitchScreenAction<EspNowSettingsMenu>, StaticMenuItemIcon<&bobbyicons::settings>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string EspNowMenu::text() const
{
    return TEXT_ESPNOW_MENU;
}

void EspNowMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
#endif
