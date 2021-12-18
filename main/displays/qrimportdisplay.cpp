constexpr const char * const TAG = "qrimport";
#include "qrimportdisplay.h"

// 3rd party includes
#include <screenmanager.h>
#include <fmt/format.h>
#include <esp_log.h>

// displays/menus includes
#include "displays/menus/greenpassmenu.h"

// local includes
#include "qrimport.h"

// m_statuslabel needs redraw

using namespace espgui;

/*
 *  This display will be accessable via GreenPassMenu. If you click on it, it will ask if you want to download the qr code.
 *  If confirm is pressed, the display will lock the back action and send a request via qrimport.h. If an error occours, it will be displayed.
 *  If everything is okay, you will be redirected to GreenPassMenu.
 *  The update function will need to be overriden to check the web handler if it exists.
 */

QrImportDisplay::QrImportDisplay()
{
    // constructor
}

void QrImportDisplay::start()
{
    m_statuslabel.start();
    qrimport::setup_request();
}

void QrImportDisplay::back()
{
    if (!m_backLocked)
        switchScreen<GreenPassMenu>();
}

void QrImportDisplay::confirm()
{
    // start request
    m_backLocked = true;
    qrimport::start_qr_request();
}

void QrImportDisplay::update()
{
    m_expected = qrimport::check_request();
    if (m_expected)
    {
        ESP_LOGI(TAG, "%s", m_expected->c_str());
        m_backLocked = false;
        switchScreen<GreenPassMenu>();
    }
}

void QrImportDisplay::redraw()
{
    if (qrimport::get_request_running())
    {
        if (!m_expected)
        {
            tft.setTextColor(TFT_RED);
            m_statuslabel.redraw(*m_expected);
            tft.setTextColor(TFT_WHITE);
        }
    }
    else
    {
        m_statuslabel.redraw(fmt::format("Request not running."));
    }
}
