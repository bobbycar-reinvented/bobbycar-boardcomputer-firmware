#pragma once

// local includes
#include "displays/menudisplaywithtime.h"

#ifdef FEATURE_LEDSTRIP
class LedstripMenu : public bobbygui::MenuDisplayWithTime
{
public:
    LedstripMenu();

    std::string text() const override;

    void back() override;
};
#endif
