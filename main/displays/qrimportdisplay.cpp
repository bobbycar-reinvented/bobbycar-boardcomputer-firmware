constexpr const char * const TAG = "qrimport";
#include "qrimportdisplay.h"

// 3rd party includes
#include <screenmanager.h>
#include <fmt/format.h>
#include <esp_log.h>

// displays/menus includes
#include "displays/menus/greenpassmenu.h"
#include "bobbyerrorhandler.h"

// local includes
#include "qrimport.h"

using namespace espgui;

QrImportDisplay::QrImportDisplay(const std::string &nvs_key) :
    m_nvs_key{nvs_key}
{
}

QrImportDisplay::QrImportDisplay(std::string &&nvs_key) :
    m_nvs_key{std::move(nvs_key)}
{
}

void QrImportDisplay::start()
{
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

void QrImportDisplay::update()
{
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

void QrImportDisplay::redraw()
{
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
        switchScreen<GreenPassMenu>();
    }
}

void QrImportDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Left:
        if (!m_waitingForResult)
            switchScreen<GreenPassMenu>();
        else
            ESP_LOGW(TAG, "tried to leave while waiting for result");
        break;
    default:;
    }
}
