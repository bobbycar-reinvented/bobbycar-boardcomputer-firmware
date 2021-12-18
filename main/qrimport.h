#pragma once
/*
 * In this file there will be
 *  - a web-handler to get qr as plain text from http://qr.bobbycar.cloud/files/[OTA_NAME].qr that can be later triggered via in qrimportdisplay.h
 *  - getter and setter that use NVS
 */

// system includes
#include <string>

// 3rd party includes
#include <tl/expected.hpp>

// local includes

namespace qrimport {
    // nvs
    tl::expected<std::string, std::string> get_qr_code(std::string_view key);
    tl::expected<void, std::string> set_qr_code(std::string_view qrcode, std::string_view key);

    // web request
    void setup_request();
    tl::expected<void, std::string> start_qr_request();
    tl::expected<std::string, std::string> check_request();
    bool get_request_running();
} // namespace
