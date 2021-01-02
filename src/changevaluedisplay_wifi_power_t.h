#pragma once

#include <WiFiGeneric.h>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<wifi_power_t> :
    public MenuDisplay,
    public virtual AccessorInterface<wifi_power_t>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    std::size_t size() const override { return 13; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_19_5dBmItem;
        case 1: return m_19dBmItem;
        case 2: return m_18_5dBmItem;
        case 3: return m_17dBmItem;
        case 4: return m_15dBmItem;
        case 5: return m_13dBmItem;
        case 6: return m_11dBmItem;
        case 7: return m_8_5dBmItem;
        case 8: return m_7dBmItem;
        case 9: return m_5dBmItem;
        case 10: return m_2dBmItem;
        case 11: return m_MINUS_1dBmItem;
        case 12: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_19_5dBmItem;
        case 1: return m_19dBmItem;
        case 2: return m_18_5dBmItem;
        case 3: return m_17dBmItem;
        case 4: return m_15dBmItem;
        case 5: return m_13dBmItem;
        case 6: return m_11dBmItem;
        case 7: return m_8_5dBmItem;
        case 8: return m_7dBmItem;
        case 9: return m_5dBmItem;
        case 10: return m_2dBmItem;
        case 11: return m_MINUS_1dBmItem;
        case 12: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_19_5dBmItem);
        callback(m_19dBmItem);
        callback(m_18_5dBmItem);
        callback(m_17dBmItem);
        callback(m_15dBmItem);
        callback(m_13dBmItem);
        callback(m_11dBmItem);
        callback(m_8_5dBmItem);
        callback(m_7dBmItem);
        callback(m_5dBmItem);
        callback(m_2dBmItem);
        callback(m_MINUS_1dBmItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_19_5dBmItem);
        callback(m_19dBmItem);
        callback(m_18_5dBmItem);
        callback(m_17dBmItem);
        callback(m_15dBmItem);
        callback(m_13dBmItem);
        callback(m_11dBmItem);
        callback(m_8_5dBmItem);
        callback(m_7dBmItem);
        callback(m_5dBmItem);
        callback(m_2dBmItem);
        callback(m_MINUS_1dBmItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_19_5dBm>> m_19_5dBmItem{WIFI_POWER_19_5dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_19dBm>> m_19dBmItem{WIFI_POWER_19dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_18_5dBm>> m_18_5dBmItem{WIFI_POWER_18_5dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_17dBm>> m_17dBmItem{WIFI_POWER_17dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_15dBm>> m_15dBmItem{WIFI_POWER_15dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_13dBm>> m_13dBmItem{WIFI_POWER_13dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_11dBm>> m_11dBmItem{WIFI_POWER_11dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_8_5dBm>> m_8_5dBmItem{WIFI_POWER_8_5dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_7dBm>> m_7dBmItem{WIFI_POWER_7dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_5dBm>> m_5dBmItem{WIFI_POWER_5dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_2dBm>> m_2dBmItem{WIFI_POWER_2dBm, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<wifi_power_t>, StaticText<TEXT_WIFI_POWER_MINUS_1dBm>> m_MINUS_1dBmItem{WIFI_POWER_MINUS_1dBm, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<wifi_power_t>::start()
{
    Base::start();

    if (getValue() == m_19_5dBmItem.value())    setSelectedIndex(0); else
    if (getValue() == m_19dBmItem.value())      setSelectedIndex(1); else
    if (getValue() == m_18_5dBmItem.value())    setSelectedIndex(2); else
    if (getValue() == m_17dBmItem.value())      setSelectedIndex(3); else
    if (getValue() == m_15dBmItem.value())      setSelectedIndex(4); else
    if (getValue() == m_13dBmItem.value())      setSelectedIndex(5); else
    if (getValue() == m_11dBmItem.value())      setSelectedIndex(6); else
    if (getValue() == m_8_5dBmItem.value())     setSelectedIndex(7); else
    if (getValue() == m_7dBmItem.value())       setSelectedIndex(8); else
    if (getValue() == m_5dBmItem.value())       setSelectedIndex(9); else
    if (getValue() == m_2dBmItem.value())       setSelectedIndex(10); else
    if (getValue() == m_MINUS_1dBmItem.value()) setSelectedIndex(11); else
    {
        Serial.printf("Unknown wifi_power_t: %i", int(getValue()));
        setSelectedIndex(12);
    }
}
}
