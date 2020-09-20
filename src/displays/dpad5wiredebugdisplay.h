#pragma once

#include "display.h"
#include "globals.h"
#include "widgets/label.h"
#include "dpad5wire.h"

namespace {
#ifdef FEATURE_DPAD_5WIRESW
class DPad5WireDebugDisplay : public Display, public virtual DummyConfirm, public virtual DummyBack
{
public:
    void initScreen() override;
    void redraw() override;

private:
    Label m_label0{30, 100};
    Label m_label1{30, 125};
    Label m_label2{30, 150};
};

void DPad5WireDebugDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString("DPad 5wire debug", 5, 5);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_label0.start();
    m_label1.start();
    m_label2.start();
}

void DPad5WireDebugDisplay::redraw()
{
    m_label0.redraw(String{} +
                    (std::get<0>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<1>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<2>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<3>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<4>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<5>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<6>(dpad5wire::lastState) ? '1' : '0') + ' ' +
                    (std::get<7>(dpad5wire::lastState) ? '1' : '0'));
    m_label1.redraw(String{raw_gas});
    m_label2.redraw(String{raw_brems});
}
#endif
}
