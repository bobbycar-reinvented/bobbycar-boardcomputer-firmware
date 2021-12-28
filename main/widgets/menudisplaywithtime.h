#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

namespace bobbygui {
class MenuDisplayWithTime :
    public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;

public:
    void start() override;
    void redraw() override;
    espgui::Label m_label_currentTime{145, 6};

private:
    virtual bool use_big_font() const
    {
#ifdef MENU_DISPLAY_USE_BIG_TIME
        return true;
#else
        return false;
#endif
    }
};
} // namespace
