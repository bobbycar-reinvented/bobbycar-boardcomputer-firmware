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
    explicit QrImportDisplay(const std::string &nvs_key);
    explicit QrImportDisplay(std::string &&nvs_key);

    void start() override;
    void update() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;

private:
    bool m_waitingForResult{false};
    espgui::Label m_statuslabel{5,(espgui::tft.height() / 2)-espgui::tft.fontHeight(4)};

    tl::expected<std::string, std::string> m_result;
    std::string m_nvs_key;
};
