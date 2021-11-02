#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <widgets/label.h>
#include <screenmanager.h>

extern espgui::Label bootLabel;

void initScreen();
void updateDisplay();
void redrawDisplay();
