#pragma once

// local includes
#include "displays/menudisplaywithtime.h"

class TimeSettingsMenu : public bobbygui::MenuDisplayWithTime
{
public:
    TimeSettingsMenu();

    std::string text() const override;

    void back() override;
};
