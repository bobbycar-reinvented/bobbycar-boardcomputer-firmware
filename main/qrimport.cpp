#include "qrimport.h"

// system includes

// 3rd party includes
#include <asynchttprequest.h>
#include <cleanuphelper.h>
#include <cpputils.h>
#include <delayedconstruction.h>

// local includes

namespace qrimport {

namespace {
cpputils::DelayedConstruction<AsyncHttpRequest> http_request;
} // namespace

// nvs
tl::expected<std::string, std::string> get_qr_code(std::string_view key)
{
    return "";
}

tl::expected<void, std::string> set_qr_code(std::string_view qrcode, std::string_view key)
{
    return{};
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

    if (const auto res = http_request->start(fmt::format("http://qr.bobbycar.cloud/{}.qr", OTA_USERNAME)); !res)
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
    else
    {
        return http_request->takeBuffer();
    }
}

bool get_request_running()
{
    if (!http_request.constructed())
    {
        return false;
    }

    return http_request->finished();
}
} // namespace
