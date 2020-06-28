#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "actioninterface.h"
#include "utils.h"
#include "actions/setvalueaction.h"
#include "actions/backproxyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<bool> :
    public MenuDisplay,
    public virtual AccessorInterface<bool>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    std::size_t size() const override { return 4; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        switch (index)
        {
        case 0: return m_trueItem;
        case 1: return m_falseItem;
        case 2: return m_backItem;
        }

        throw "aua";
    }
    const MenuItem& getMenuItem(std::size_t index) const override
    {
        switch (index)
        {
        case 0: return m_trueItem;
        case 1: return m_falseItem;
        case 2: return m_backItem;
        }

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(m_trueItem);
        callback(m_falseItem);
        callback(m_backItem);
    }
    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(m_trueItem);
        callback(m_falseItem);
        callback(m_backItem);
    }

private:
    makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_TRUE>> m_trueItem{true, *this, *this};
    makeComponentArgs<MenuItem, SetValueAction<bool>, StaticText<TEXT_FALSE>> m_falseItem{false, *this, *this};
    makeComponentArgs<MenuItem, BackProxyAction, StaticText<TEXT_BACK>, StaticMenuItemIcon<&icons::back>> m_backItem{*this};
};

void ChangeValueDisplay<bool>::start()
{
    Base::start();

    if (getValue() == m_trueItem.value())  setSelectedIndex(0); else
    if (getValue() == m_falseItem.value()) setSelectedIndex(1);
}
}
