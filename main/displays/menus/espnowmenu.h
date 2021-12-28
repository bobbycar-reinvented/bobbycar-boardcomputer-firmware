#pragma once

#ifdef FEATURE_ESPNOW

// 3rdparty lib includes
#include <accessorinterface.h>
#include <actioninterface.h>
#include <espchrono.h>
#include <fmt/core.h>
#include <menudisplay.h>
#include <textinterface.h>
#include <texts.h>

// local includes
#include "displays/bobbymenudisplay.h"
#include "espnowfunctions.h"

using namespace espgui;

namespace espnowmenu {

struct ReceiveTimeStampAccessor : public RefAccessor<bool> { bool &getRef() const override { return espnow::receiveTimeStamp; } };
struct ReceiveTsFromOtherBobbycarsAccessor : public RefAccessor<bool> { bool &getRef() const override { return espnow::receiveTsFromOtherBobbycars; } };

class SendBobbycarTimesyncMessageAction : public virtual ActionInterface {
public:
    void triggered() override
    {
        const auto message = fmt::format("BOBBYT:{}", espchrono::utc_clock::now().time_since_epoch().count());
        espnow::send_espnow_message(message);
    }
};

} // namespace

class EspNowMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_ESPNOW_MENU>
{
public:
    EspNowMenu();
    void back() override;
};

#endif
