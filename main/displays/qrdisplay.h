#pragma once

// 3rd party includes
#include <display.h>
#include <qrcode.h>

class QrDisplay :
        public espgui::Display
{
public:
    QrDisplay(std::string_view msg, uint8_t ver);
    void initScreen() override;
    void confirm() override;
    void back() override;
private:
    std::string_view m_msg;
    uint8_t m_ver;
};
