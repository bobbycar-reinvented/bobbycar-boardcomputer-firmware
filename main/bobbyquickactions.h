#pragma once

// 3rdparty lib includes
#include <buttonsinterface.h>

// local includes
#include "bobbybuttons.h"

namespace bobby::quickactions {

void handle_bobby_quickaction(espgui::Button button, bool pressed = true);

// functions
void open_garage();
void blink_left();
void blink_right();
void handle_handbremse();
void action_wifi_scan();
void handle_pwmomat();

} // namespace bobby::quickactions
