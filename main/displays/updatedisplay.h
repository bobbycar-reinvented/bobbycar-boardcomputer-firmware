#pragma once

// 3rdparty lib includes

// local includes
#include "display.h"
#include "widgets/label.h"
#include "widgets/progressbar.h"

#ifdef FEATURE_OTA
class UpdateDisplay : public espgui::Display
{
    using Base = espgui::Display;
public:
    void initScreen() override;
    void redraw() override;
    void confirm() override;
    void back() override;

private:
    espgui::Label m_statusLabel{120, 75};
    espgui::Label m_progressLabel{120, 100};
    espgui::Label m_totalLabel{120, 125};
    espgui::Label m_messageLabel{20, 150};

    espgui::ProgressBar m_progressBar{20, 200, 200, 10, 0, 100};

    espgui::Label m_newVersionLabel{20, 275};
};
#endif
