#pragma once

// local includes
#include "displays/menudisplaywithtime.h"

class GitMenu : public bobbygui::MenuDisplayWithTime
{
public:
    GitMenu();

    std::string text() const override;

    void back() override;
};
