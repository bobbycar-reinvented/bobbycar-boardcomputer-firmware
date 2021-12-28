#pragma once

// 3rd party includes
#include <widgets/label.h>
#include <tftinstance.h>
#include <tl/expected.hpp>

// local includes
#include "bobbydisplay.h"

class QrImportDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    QrImportDisplay(std::string nvs_key);

    void start() override;
    void update() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;

private:
    bool m_confirmLocked{false};
    espgui::Label m_statuslabel{5,(espgui::tft.height() / 2)-espgui::tft.fontHeight(4)};
    tl::expected<std::string, std::string> m_expected;
    std::string m_nvs_key;
};
