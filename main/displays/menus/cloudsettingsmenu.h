#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

#ifdef FEATURE_CLOUD
class CloudSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_CLOUDSETTINGS>
{
public:
    CloudSettingsMenu();

    void back() override;
};
#endif
