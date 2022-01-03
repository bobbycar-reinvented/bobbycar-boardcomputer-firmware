#pragma once

// system includes
#include <optional>
#include <nvs.h>

class SettingsPersister
{
public:
    bool init();
    bool erase();
    bool openProfile(uint8_t index);
    void closeProfile();

    template<typename T>
    bool load(T &profileSettings);

    template<typename T>
    bool save(T &profileSettings);

    std::optional<uint8_t> currentlyOpenProfileIndex() const;

private:

    struct CurrentlyOpenProfile {
        nvs_handle handle;
        uint8_t profileIndex;
    };
    std::optional<CurrentlyOpenProfile> m_profile;
};
