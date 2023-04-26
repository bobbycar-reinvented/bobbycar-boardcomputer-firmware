#include "qrimport.h"

// esp-idf includes
#include <esp_log.h>
#include <nvs.h>

// 3rd party includes
#include <ArduinoJson.h>
#include <asynchttprequest.h>
#include <cleanuphelper.h>
#include <delayedconstruction.h>

// local includes
#include "newsettings.h"

namespace qrimport {

namespace {
constexpr const char * const TAG = "QRIMPORT";

cpputils::DelayedConstruction<AsyncHttpRequest> http_request;
} // namespace

// nvs
bool has_qr_code(std::string_view key)
{
    const auto handle = configs.nvs_handle_user;

    size_t length;
    if (const esp_err_t result = nvs_get_str(handle, key.data(), nullptr, &length); result != ESP_OK)
    {
        if (result != ESP_ERR_NVS_NOT_FOUND)
            ESP_LOGW(TAG, "nvs_get_str() size-only for key %.*s failed with %s", key.size(), key.data(), esp_err_to_name(result));
        return false;
    }

    return length;
}

tl::expected<std::string, esp_err_t> get_qr_code(std::string_view key)
{
    const auto handle = configs.nvs_handle_user;

    size_t length;
    if (const esp_err_t result = nvs_get_str(handle, key.data(), nullptr, &length); result != ESP_OK)
    {
        if (result != ESP_ERR_NVS_NOT_FOUND)
            ESP_LOGW(TAG, "nvs_get_str() size-only for key %.*s failed with %s", key.size(), key.data(), esp_err_to_name(result));
        return tl::make_unexpected(result);
    }

    // empty string optimization
    if (!length)
        return {};

    std::string buf;
    buf.resize(length);
    if (const esp_err_t result = nvs_get_str(handle, key.data(), buf.data(), &length); result != ESP_OK)
    {
        ESP_LOGW(TAG, "nvs_get_str() for key %.*s failed with %s", key.size(), key.data(), esp_err_to_name(result));
        return tl::make_unexpected(result);
    }

    if (buf.back() == '\n')
        buf.resize(buf.size() - 1);

    return buf; // no std::move needed as return is optimized
}

tl::expected<void, esp_err_t> set_qr_code(std::string_view key, std::string_view qrcode)
{
    const auto handle = configs.nvs_handle_user;

    if (const esp_err_t result = nvs_set_str(handle, key.data(), qrcode.data()); result != ESP_OK)
    {
        ESP_LOGW(TAG, "nvs_set_str() for key %.*s failed with %s", key.size(), key.data(), esp_err_to_name(result));
        return tl::make_unexpected(result);
    }

    return {};
}

tl::expected<void, esp_err_t> delete_qr_code(std::string_view key)
{
    const auto handle = configs.nvs_handle_user;

    if (const esp_err_t result = nvs_erase_key(handle, key.data()); result != ESP_OK)
    {
        ESP_LOGW(TAG, "nvs_erase_key() for key %.*s failed with %s", key.size(), key.data(), esp_err_to_name(result));
        return tl::make_unexpected(result);
    }

    return {};
}

// web request
void setup_request()
{
    if (!http_request.constructed())
    {
        http_request.construct("qr_request", espcpputils::CoreAffinity::Core0);
    }
}

tl::expected<void, std::string> start_qr_request()
{
    if (!http_request.constructed())
    {
        return tl::make_unexpected("request im oarsch");
    }

    const auto url = fmt::format("http://service.bobbycar.cloud/api/qr/{}.qr", configs.otaUsername.value());

    ESP_LOGI(TAG, "starting request to %s", url.c_str());

    if (auto res = http_request->start(url); !res)
    {
        return res;
    }
    return{};
}

tl::expected<std::string, std::string> check_request()
{
    if (!http_request.constructed())
    {
        return tl::make_unexpected("request im oarsch");
    }

    if (!http_request->finished())
    {
        return tl::make_unexpected("request has not finished");
    }

    const auto helper = cpputils::makeCleanupHelper([](){ http_request->clearFinished(); });

    if (const auto result = http_request->result(); !result)
    {
        return tl::make_unexpected(result.error());
    }
    else if (http_request->statusCode() != 200)
    {
        DynamicJsonDocument doc(256);
        deserializeJson(doc, http_request->takeBuffer());
        return tl::make_unexpected(fmt::format("{} {}", http_request->statusCode(), doc["error"].as<std::string>()));
    }
    else
    {
        ESP_LOGI(TAG, "%.*s", http_request->buffer().size(), http_request->buffer().data());
        return http_request->takeBuffer();
    }
}

bool get_request_running()
{
    if (!http_request.constructed())
    {
        ESP_LOGW(TAG, "not constructed");
        return false;
    }

    return !http_request->finished();
}
} // namespace
