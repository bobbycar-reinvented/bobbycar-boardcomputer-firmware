#pragma once

// 3rdparty lib includes
#include <menudisplay.h>

// local includes
#include "texts.h"

using namespace espgui;

namespace {
class CurrentVersionText : public virtual TextInterface { public: std::string text() const override {
#ifdef FEATURE_OTA
        if (const esp_app_desc_t *app_desc = esp_ota_get_app_description())
        {
            return fmt::format("Version: {}", app_desc->version);
        }
#endif
        return "Version: 1.0";
    };
};

constexpr char TEXT_VERSION[] = "Version: 1.0";

class AboutMenu :
    public MenuDisplay,
    public StaticText<TEXT_ABOUT>
{
public:
    AboutMenu();

    void back() override;
};
} // namespace
