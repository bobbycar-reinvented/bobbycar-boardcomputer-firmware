#pragma once

#include <menudisplay.h>

namespace bobbygui {
class MenuDisplayWithTime :
        public espgui::MenuDisplay
{
    using Base = espgui::MenuDisplay;
public:
    void start() override;
    void redraw() override;
    espgui::Label m_label_currentTime{145, 6};
};
} // namespace
