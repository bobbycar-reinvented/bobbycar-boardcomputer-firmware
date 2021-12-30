#pragma once

// Local includes
#include "displays/menudisplaywithtime.h"

class StatisticsMenu : public bobbygui::MenuDisplayWithTime
{
public:
    StatisticsMenu();

    std::string text() const override;

    void back() override;
};
