#pragma once

// system includes
#include <vector>

// Arduino includes
#include <Arduino.h>
#include <WiFi.h>

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/multiaction.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "types.h"

// forward declares
namespace {
class WifiSettingsMenu;
} // namespace

namespace {
class WifiScanMenu : public MenuDisplay, public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>
{
    using Base = MenuDisplay;

public:
    String text() const override;

    void start() override;
    void update() override;
    void stop() override;

    std::size_t size() const override { return 1 + vec.size(); }

    MenuItem& getMenuItem(std::size_t index) override
    {
        if (index < vec.size())
            return vec[index];

        if (index == vec.size())
            return m_backItem;

        throw "aua";
    }

    const MenuItem& getMenuItem(std::size_t index) const override
    {
        if (index < vec.size())
            return vec[index];

        if (index == vec.size())
            return m_backItem;

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        for (auto &item : vec)
            callback(item);
        callback(m_backItem);
    }

    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        for (auto &item : vec)
            callback(item);
        callback(m_backItem);
    }

private:
    makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>> m_backItem;

    std::vector<makeComponent<MenuItem, ChangeableText, DummyAction>> vec;

    millis_t m_lastScanComplete;
};

String WifiScanMenu::text() const
{
    auto text = String{vec.size()} + " found";
    switch (WiFi.scanComplete())
    {
    case WIFI_SCAN_RUNNING: text += " (scanning)"; break;
    case WIFI_SCAN_FAILED: text += " (error)"; break;
    }
    return text;
}

void WifiScanMenu::start()
{
    Base::start();

    m_lastScanComplete = 0;

    WiFi.scanNetworks(true);
}

void WifiScanMenu::update()
{
    const auto n = WiFi.scanComplete();
    if (n >= 0)
    {
        if (n != vec.size())
        {
            while (n > vec.size())
            {
                vec.emplace_back();
                vec.back().start();
            }

            while (n < vec.size())
            {
                vec.back().stop();
                vec.pop_back();
            }
        }

        const auto now = millis();
        if (!m_lastScanComplete)
        {
            for (auto iter = std::begin(vec); iter != std::end(vec); iter++)
                iter->setTitle(WiFi.SSID(std::distance(std::begin(vec), iter)));

            m_lastScanComplete = now;
        }
        else if (now - m_lastScanComplete >= 2000)
        {
            m_lastScanComplete = 0;
            WiFi.scanNetworks(true);
        }
    }

    Base::update();
}

void WifiScanMenu::stop()
{
    WiFi.scanDelete();
}
} // namespace
