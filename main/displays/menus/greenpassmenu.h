#pragma once

#include <qrcode.h>

// local includes
#include "menudisplay.h"
#include "texts.h"

namespace greenpassmenu {
extern bool showingQRCode;
} // namespace

class GreenPassMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_GREENPASS>
{
    using Base = espgui::MenuDisplay;
public:
    GreenPassMenu();
    void back() override;
    void rotate(int offset) override;
    void initScreen() override;

    class ShowCertAction : public virtual espgui::ActionInterface {
    public:
        void triggered() override;
    private:
        qrcode::QRcode m_qrcode{};
    };
};
