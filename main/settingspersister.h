#pragma once

// system includes
#include <optional>
#include <nvs.h>

class SettingsPersister
{
public:
    bool init();
    bool erase();
    bool openCommon();
    void closeCommon();
    bool openProfile(uint8_t index);
    void closeProfile();

    template<typename T>
    bool load(T &settings);

    template<typename T>
    bool save(T &settings);

    std::optional<uint8_t> currentlyOpenProfileIndex() const;

    nvs_handle getCommonHandle() { return m_handle; }

private:
    // for common settings
    nvs_handle m_handle{};

    struct CurrentlyOpenProfile {
        nvs_handle handle;
        uint8_t profileIndex;
    };
    std::optional<CurrentlyOpenProfile> m_profile;
};
