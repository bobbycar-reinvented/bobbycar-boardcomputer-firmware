#pragma once

#include <esp_wifi_types.h>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_mode_t> :
    public MenuDisplay,
    public virtual AccessorInterface<wifi_mode_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    std::size_t size() const override { return 5; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_nullItem;
        case 1: return m_staItem;
        case 2: return m_apItem;
        case 3: return m_apStaItem;
        case 4: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_nullItem;
        case 1: return m_staItem;
        case 2: return m_apItem;
        case 3: return m_apStaItem;
        case 4: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_nullItem);
        callback(m_staItem);
        callback(m_apItem);
        callback(m_apStaItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_nullItem);
        callback(m_staItem);
        callback(m_apItem);
        callback(m_apStaItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_WIFI_MODE_NULL>> m_nullItem{WIFI_MODE_NULL, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_WIFI_MODE_STA>> m_staItem{WIFI_MODE_STA, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_WIFI_MODE_AP>> m_apItem{WIFI_MODE_AP, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_mode_t>, StaticText<TEXT_WIFI_MODE_APSTA>> m_apStaItem{WIFI_MODE_APSTA, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<wifi_mode_t>::start()
{
    Base::start();

    if (getValue() == m_nullItem.value())  setSelectedIndex(0); else
    if (getValue() == m_staItem.value())   setSelectedIndex(1); else
    if (getValue() == m_apItem.value())    setSelectedIndex(2); else
    if (getValue() == m_apStaItem.value()) setSelectedIndex(3); else
    {
        Serial.printf("Unknown wifi_mode_t: %i", int(getValue()));
        setSelectedIndex(4);
    }
}
}
