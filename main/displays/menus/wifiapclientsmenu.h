#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "displays/bobbymenudisplay.h"

class WifiApClientsMenu :
    public BobbyMenuDisplay,
    public virtual espgui::ChangeableText
{
    using Base = BobbyMenuDisplay;

public:
    WifiApClientsMenu();

    void back() override;

    void start() override;
    void update() override;

private:
    void doSyncItems();

private:
    espchrono::millis_clock::time_point m_lastSync;
};
