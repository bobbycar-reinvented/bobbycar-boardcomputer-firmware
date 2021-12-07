#pragma once

// Local includes
#include "menudisplay.h"
#include "texts.h"

#ifdef FEATURE_LEDSTRIP

class currentSelectedAnimationText : public virtual espgui::TextInterface {
public:
    std::string text() const override;
};

class LedstripSelectAnimationMenu :
        public espgui::MenuDisplay,
        public espgui::StaticText<TEXT_SELECTANIMATION>
{
public:
    LedstripSelectAnimationMenu();
    void back() override;
};
#endif
