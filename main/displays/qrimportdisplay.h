#pragma once

// 3rd party includes
#include <esp_log.h>
#include <fmt/core.h>
#include <tftinstance.h>
#include <tl/expected.hpp>
#include <widgets/label.h>

// local includes
#include "bobbydisplay.h"
#include "bobbyerrorhandler.h"
#include "qrimport.h"
#include "screenmanager.h"

class QrImportDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    explicit QrImportDisplay(const std::string &nvs_key) : m_nvs_key{nvs_key} {}
    explicit QrImportDisplay(std::string &&nvs_key) : m_nvs_key{std::move(nvs_key)} {}

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
