#include "qrcodedebug.h"

#include <esp_log.h>

#include "screenmanager.h"
#include "displays/menus/debugmenu.h"

using namespace espgui;

QrCodeDebugDisplay::QrCodeDebugDisplay()
{
}

void QrCodeDebugDisplay::back()
{
    switchScreen<DebugMenu>();
}

void QrCodeDebugDisplay::initScreen()
{
    Base::initScreen();
    m_qrcode.init();
}

void QrCodeDebugDisplay::confirm()
{
    m_qrcode.createScaleToFit("WIFI:T:WPA;S:realraum;P:r3alraum;");
}

void QrCodeDebugDisplay::rotate(int offset)
{
    m_mult += offset;
    m_qrcode.setMultiply(m_mult);
    ESP_LOGW("BOBBY", "Multiply: %i", m_mult);
    m_qrcode.create("Hello World!");
}
