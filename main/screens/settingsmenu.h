#pragma once

// local includes
#include "guihelpers/menudisplaywithtime.h"

namespace bobby {

class SettingsMenu : public bobby::MenuDisplayWithTime
{
public:
    SettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
