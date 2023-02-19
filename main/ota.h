#pragma once

// system includes
#include <optional>
#include <string>
#include <string_view>

// esp-idf includes
#include <esp_app_desc.h>

// 3rdparty lib includes
#include <espasyncota.h>
#include <tl/expected.hpp>

namespace bobby::ota {

extern std::optional<esp_app_desc_t> otherAppDesc;

void initOta();

void handleOta();

tl::expected<void, std::string> triggerOta(std::string_view url);

tl::expected<void, std::string> switchAppPartition();

bool isOtaInProgress();

int otaProgress();

std::optional<int> otaTotalSize();

float otaPercent();

const std::string &otaMessage();

const std::optional<esp_app_desc_t> &otaAppDesc();

OtaCloudUpdateStatus otaStatus();

} // namespace bobby::ota
