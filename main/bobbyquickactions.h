#pragma once

// 3rdparty lib includes
#include <buttonsinterface.h>
#include <cpptypesafeenum.h>

// local includes
#include "bobbybuttons.h"

#define BobbyQuickActionsValues(x) \
    x(NONE) \
    x(BLINK_LEFT) \
    x(BLINK_RIGHT) \
    x(HANDBREMSE) \
    x(OPEN_GARAGE) \
    x(WIFI_SCAN) \
    x(PWMOMAT) \
    x(HUPE) \
    x(COMPRESSOR_TOGGLE)

DECLARE_TYPESAFE_ENUM(BobbyQuickActions, : uint8_t, BobbyQuickActionsValues)

namespace quickactions {

void handle_bobby_quickaction(espgui::Button button, bool pressed = true);

// functions
void open_garage();
void blink_left();
void blink_right();
void handle_handbremse();
void action_wifi_scan();
void handle_pwmomat();

} // namespace quickactions
