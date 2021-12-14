#include "menudisplaywithtime.h"
#include "tftinstance.h"
#include "utils.h"

using namespace espgui;

namespace bobbygui {
void MenuDisplayWithTime::start()
{
    Base::start();
    m_label_currentTime.start();
}

void MenuDisplayWithTime::redraw()
{
    Base::redraw();
    tft.setTextFont(2);
    m_label_currentTime.redraw(fmt::format("&7Time: {}", local_clock_string()));
}

} // namespace
