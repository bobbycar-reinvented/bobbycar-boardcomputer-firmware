#pragma once

// 3rdparty lib includes
#include <cpptypesafeenum.h>
#include <buttonsinterface.h>

// local includes
#include "bobbybuttons.h"

#define BobbyQuickActionsValues(x) \
    x(NONE) \
    x(BLINK_LEFT) \
    x(BLINK_RIGHT) \
    x(HANDBREMSE) \
    x(OPEN_GARAGE)
DECLARE_TYPESAFE_ENUM(BobbyQuickActions, : uint8_t, BobbyQuickActionsValues)

namespace quickactions {

void handle_bobby_quickaction(espgui::Button button);

// functions
void open_garage();
void blink_left();
void blink_right();
void handle_handbremse();

} // namespace quickactions
