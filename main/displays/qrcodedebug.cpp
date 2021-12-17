#include "qrcodedebug.h"

#include <fmt/core.h>

#include "displays/menus/debugmenu.h"
#include "globals.h"
#include "screenmanager.h"

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
    m_qrcode.createScaleToFit(fmt::format("WIFI:T:WPA;S:{};P:{};", deviceName, stringSettings.ap_password));
}

void QrCodeDebugDisplay::rotate(int offset)
{
    m_mult += offset;
    m_qrcode.setMultiply(m_mult);
    m_qrcode.create("Hello World!");
}
