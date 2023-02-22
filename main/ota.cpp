#include "ota.h"

// esp-idf includes
#include <esp_image_format.h>
#include <esp_log.h>
#include <esp_ota_ops.h>

// 3rdparty lib includes
#include <cpputils.h>
#include <delayedconstruction.h>
#include <espasyncota.h>
#include <recursivelockhelper.h>

// local includes
#include "globallock.h"

namespace bobby::ota {
namespace {
constexpr const char *const TAG = "BOBBYOTA";

cpputils::DelayedConstruction<EspAsyncOta> _asyncOta;
} // namespace

std::optional<esp_app_desc_t> otherAppDesc;

void initOta()
{
    _asyncOta.construct("asyncOtaTask", 8192u, espcpputils::CoreAffinity::Core0);

    readOtaAppInfo();
}

void handleOta()
{
    if (!_asyncOta)
        return;

    espcpputils::RecursiveLockHelper lockHelper{global_lock->handle};

    _asyncOta->update();
}

tl::expected<void, std::string> triggerOta(std::string_view url)
{
    if (!_asyncOta)
        return tl::make_unexpected("OTA not initialized");

    espcpputils::RecursiveLockHelper lockHelper{global_lock->handle};

    return _asyncOta->trigger(url, {}, {}, {});
}

tl::expected<void, std::string> switchAppPartition()
{
    auto partition = esp_ota_get_boot_partition();
    if (!partition)
    {
        ESP_LOGE(TAG, "Failed to get boot partition");
        return tl::make_unexpected("Failed to get boot partition");
    }

    partition = esp_ota_get_next_update_partition(partition);
    if (!partition)
    {
        ESP_LOGE(TAG, "Failed to get next update partition");
        return tl::make_unexpected("Failed to get next update partition");
    }

    const esp_partition_pos_t partitionPos = {
        .offset = partition->address,
        .size = partition->size,
    };

    esp_image_metadata_t metadata;
    if (const auto res = esp_image_verify(ESP_IMAGE_VERIFY, &partitionPos, &metadata); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to verify image: %s", esp_err_to_name(res));
        return tl::make_unexpected("Failed to verify image");
    }

    if (const auto res = esp_ota_set_boot_partition(partition); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set boot partition: %s", esp_err_to_name(res));
        return tl::make_unexpected("Failed to set boot partition");
    }

    ESP_LOGI(TAG, "Switched to partition %s", partition->label);
    return {};
}

tl::expected<void, std::string> readOtaAppInfo()
{
    otherAppDesc = std::nullopt;

    auto partition = esp_ota_get_boot_partition();
    if (!partition)
    {
        ESP_LOGE(TAG, "Failed to get boot partition");
        return tl::make_unexpected("Failed to get boot partition");
    }

    partition = esp_ota_get_next_update_partition(partition);
    if (!partition)
    {
        ESP_LOGE(TAG, "Failed to get next update partition");
        return tl::make_unexpected("Failed to get next update partition");
    }

    const esp_partition_pos_t partitionPos = {
            .offset = partition->address,
            .size = partition->size,
    };

    esp_image_metadata_t metadata;
    if (const auto res = esp_image_verify(ESP_IMAGE_VERIFY, &partitionPos, &metadata); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to verify image: %s", esp_err_to_name(res));
        return tl::make_unexpected("Failed to verify image");
    }

    esp_app_desc_t appDesc;
    if (const auto res = esp_ota_get_partition_description(partition, &appDesc); res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get partition description: %s", esp_err_to_name(res));
        return tl::make_unexpected("Failed to get partition description");
    }

    otherAppDesc = appDesc;

    return {};
}

bool isOtaInProgress()
{
    return !cpputils::is_in(_asyncOta->status(), OtaCloudUpdateStatus::Idle, OtaCloudUpdateStatus::NotReady);
}

int otaProgress()
{
    if (!_asyncOta)
        return 0;

    return _asyncOta->progress();
}

std::optional<int> otaTotalSize()
{
    if (!_asyncOta)
        return std::nullopt;

    return _asyncOta->totalSize();
}

float otaPercent()
{
    if (!_asyncOta)
        return 0;

    const auto progress = _asyncOta->progress();
    const auto totalSize = _asyncOta->totalSize();

    if (!totalSize)
        return 0;

    return static_cast<float>(progress) / static_cast<float>(*totalSize) * 100.0f;
}

const std::string &otaMessage()
{
    static const std::string noMessage;
    if (!_asyncOta)
        return noMessage;

    return _asyncOta->message();
}

const std::optional<esp_app_desc_t> &otaAppDesc()
{
    static const std::optional<esp_app_desc_t> noAppDesc;
    if (!_asyncOta)
        return noAppDesc;

    return _asyncOta->appDesc();
}

OtaCloudUpdateStatus otaStatus()
{
    if (!_asyncOta)
        return OtaCloudUpdateStatus::NotReady;

    return _asyncOta->status();
}

bool isConstructed()
{
    return _asyncOta;
}
} // namespace bobby::ota
