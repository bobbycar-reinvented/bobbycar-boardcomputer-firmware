#pragma once

// local includes
#include "displays/menudisplaywithtime.h"

class SettingsMenu : public bobbygui::MenuDisplayWithTime
{
public:
    SettingsMenu();

    std::string text() const override;

    void back() override;
};
