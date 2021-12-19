#pragma once

// 3rd party includes
#include <display.h>
#include <widgets/label.h>
#include <tftinstance.h>
#include <tl/expected.hpp>

class QrImportDisplay : public espgui::Display
{
    using Base = espgui::Display;
public:
    QrImportDisplay(std::string nvs_key);
    void start() override;
    void back() override;
    void update() override;
    void redraw() override;
    void confirm() override;
private:
    bool m_confirmLocked{false};
    espgui::Label m_statuslabel{5,(espgui::tft.height() / 2)-espgui::tft.fontHeight(4)};
    tl::expected<std::string, std::string> m_expected;
    std::string m_nvs_key;
};
