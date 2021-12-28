#pragma once

// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"

// local includes
#include "displays/bobbymenudisplay.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "texts.h"
#include "utils.h"

class WifiScanMenu :
    public BobbyMenuDisplay,
    public espgui::BackActionInterface<espgui::SwitchScreenAction<StationWifiSettingsMenu>>
{
    using Base = BobbyMenuDisplay;

public:
    WifiScanMenu();

    std::string text() const override;

    void start() override;
    void update() override;
    void stop() override;
    void back() override;

private:
    std::optional<espchrono::millis_clock::time_point> m_lastScanComplete;

    using menu_item_t = espgui::makeComponent<espgui::MenuItem, espgui::ChangeableText, espgui::DummyAction>;
    std::vector<std::unique_ptr<menu_item_t>> m_reusableItems;
};
