#pragma once
constexpr const char * const TAG = "qrimport";

// 3rd party includes
#include <esp_log.h>
#include <widgets/label.h>
#include <tftinstance.h>
#include <tl/expected.hpp>
#include <fmt/core.h>

// local includes
#include "bobbydisplay.h"
#include "bobbyerrorhandler.h"
#include "qrimport.h"
#include "screenmanager.h"

template<typename TMenu>
class QrImportDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    explicit QrImportDisplay(const std::string &nvs_key) : m_nvs_key{nvs_key} {}
    explicit QrImportDisplay(std::string &&nvs_key) : m_nvs_key{std::move(nvs_key)} {}

    void start() override
    {
        using namespace espgui;
        Base::start();

        m_statuslabel.start();

        qrimport::setup_request();

        if (const auto result = qrimport::start_qr_request(); result)
        {
            ESP_LOGI(TAG, "started request, waiting for result");
            m_waitingForResult = true;
        }
        else
        {
            ESP_LOGE(TAG, "could not start request: %.*s", result.error().size(), result.error().data());
            m_result = tl::make_unexpected(std::move(result).error());
        }
    }

    void update() override
    {
        using namespace espgui;
        Base::update();

        if (!m_waitingForResult)
            return;

        if (qrimport::get_request_running())
            return;

        m_waitingForResult = false;

        m_result = qrimport::check_request();
        if (m_result)
        {
            ESP_LOGI(TAG, "%.*s => %.*s", m_nvs_key.size(), m_nvs_key.data(), m_result->size(), m_result->data());
            if (const auto result = qrimport::set_qr_code(m_nvs_key, *m_result); !result)
                m_result = tl::make_unexpected(fmt::format("saving qr failed: {}", esp_err_to_name(result.error())));
        }
        else
            ESP_LOGW(TAG, "failed %.*s => %.*s", m_nvs_key.size(), m_nvs_key.data(), m_result.error().size(), m_result.error().data());
    }

    void redraw() override
    {
        using namespace espgui;
        Base::redraw();

        if (m_waitingForResult)
        {
            tft.setTextColor(TFT_YELLOW, TFT_BLACK);
            m_statuslabel.redraw("In progress");
        }
        else if (!m_result && !m_result.error().empty())
        {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            BobbyErrorHandler{}.errorOccured(fmt::format("Error: {}", m_result.error()));
            m_result.error().clear();
        }
        else
        {
            tft.setTextColor(TFT_GREEN, TFT_BLACK);
            m_statuslabel.redraw("OK");
            switchScreen<TMenu>();
        }
    }

    void buttonPressed(espgui::Button button) override
    {
        using namespace espgui;
        Base::buttonPressed(button);

        switch (button)
        {
            using espgui::Button;
            case Button::Left:
                if (!m_waitingForResult)
                    switchScreen<TMenu>();
                else
                    ESP_LOGW(TAG, "tried to leave while waiting for result");
                break;
            default:;
        }
    }

private:
    bool m_waitingForResult{false};
    espgui::Label m_statuslabel{5,(espgui::tft.height() / 2)-espgui::tft.fontHeight(4)};

    tl::expected<std::string, std::string> m_result;
    std::string m_nvs_key;
};
