#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<>
class ChangeValueDisplay<LarsmModeMode> :
    public MenuDisplay,
    public virtual AccessorInterface<LarsmModeMode>,
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
        case 0: return m_larsmMode1Item;
        case 1: return m_larsmMode2Item;
        case 2: return m_larsmMode3Item;
        case 3: return m_larsmMode4Item;
        case 4: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_larsmMode1Item;
        case 1: return m_larsmMode2Item;
        case 2: return m_larsmMode3Item;
        case 3: return m_larsmMode4Item;
        case 4: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_larsmMode1Item);
        callback(m_larsmMode2Item);
        callback(m_larsmMode3Item);
        callback(m_larsmMode4Item);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_larsmMode1Item);
        callback(m_larsmMode2Item);
        callback(m_larsmMode3Item);
        callback(m_larsmMode4Item);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<LarsmModeMode>, StaticText<TEXT_LARSMMODE1>> m_larsmMode1Item{LarsmModeMode::Mode1, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<LarsmModeMode>, StaticText<TEXT_LARSMMODE2>> m_larsmMode2Item{LarsmModeMode::Mode2, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<LarsmModeMode>, StaticText<TEXT_LARSMMODE3>> m_larsmMode3Item{LarsmModeMode::Mode3, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<LarsmModeMode>, StaticText<TEXT_LARSMMODE4>> m_larsmMode4Item{LarsmModeMode::Mode4, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<LarsmModeMode>::start()
{
    Base::start();

    if (getValue() == m_larsmMode1Item.value()) setSelectedIndex(0); else
    if (getValue() == m_larsmMode2Item.value()) setSelectedIndex(1); else
    if (getValue() == m_larsmMode3Item.value()) setSelectedIndex(2); else
    if (getValue() == m_larsmMode4Item.value()) setSelectedIndex(3); else
    {
        Serial.printf("Unknown LarsmModeMode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}
}
