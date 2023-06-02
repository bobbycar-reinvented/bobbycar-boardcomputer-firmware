#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <qrcodegen.hpp>

// local includes
#include "guihelpers/bobbydisplay.h"

namespace bobby {

class QrCodeDebugDisplay :
    public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    using Base::Base;

    void redraw(espgui::TftInterface &tft) override;

    void buttonPressed(espgui::Button button) override;

private:
    std::optional<qrcodegen::QrCode> m_qrcode;
};
} // namespace bobby
