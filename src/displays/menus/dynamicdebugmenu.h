#pragma once

// Arduino includes
#include <Arduino.h>
#include <WString.h>

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "actions/toggleboolaction.h"
#include "icons/lock.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "types.h"

// forward declares
namespace {
class DebugMenu;
} // namespace

namespace {
class RandomText : public virtual TextInterface
{
public:
    String text() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_title = String{"Dynamic text: "} + random(0, 100);
            m_nextUpdate = now + random(0, 1000);
        }

        return m_title;
    }

private:
    mutable millis_t m_nextUpdate{};
    mutable String m_title;
};

class RandomColor : public virtual ColorInterface
{
public:
    int color() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            const auto count = std::distance(std::begin(default_4bit_palette), std::end(default_4bit_palette));
            m_color = default_4bit_palette[random(0, count)];
            m_nextUpdate = now + random(0, 1000);
        }

        return m_color;
    }

private:
    mutable millis_t m_nextUpdate{};
    mutable int m_color;
};

class RandomFont : public virtual FontInterface
{
public:
    int font() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            m_font = random(1, 5);
            m_nextUpdate = now + random(0, 1000);
        }

        return m_font;
    }

private:
    mutable millis_t m_nextUpdate{};
    mutable int m_font;
};

class RandomIcon : public virtual MenuItemIconInterface
{
public:
    const MenuItemIcon *icon() const override
    {
        const auto now = millis();
        if (!m_nextUpdate || now >= m_nextUpdate)
        {
            if (m_icon)
                m_icon = nullptr;
            else
                m_icon = &icons::lock;
            m_nextUpdate = now + random(0, 1000);
        }

        return m_icon;
    }

private:
    mutable millis_t m_nextUpdate{};
    mutable const Icon<24, 24> *m_icon;
};

bool toggle;
struct ToggleAccessor : public virtual RefAccessor<bool>
{
public:
    bool &getRef() const override { return toggle; }
};

constexpr char TEXT_DUMMYITEM[] = "Dummy item";
constexpr char TEXT_DYNAMICCOLOR[] = "Dynamic color";
constexpr char TEXT_DYNAMICFONT[] = "Dynamic font";
constexpr char TEXT_DYNAMICICON[] = "Dynamic icon";
constexpr char TEXT_STATICICON[] = "Static icon";
constexpr char TEXT_DEBUGTOGGLE[] = "Toggle";

class DynamicDebugMenu :
    public MenuDisplay,
    public RandomText,
    public BackActionInterface<SwitchScreenAction<DebugMenu>>,
    public ContainerMenuDefinition
{
public:
    DynamicDebugMenu()
    {
        // dummy items to allow for scrolling
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();

        // the interesting bits
        constructItem<makeComponent<MenuItem, RandomText,                    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DYNAMICCOLOR>, RandomColor, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DYNAMICFONT>,  RandomFont, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DYNAMICICON>,  RandomIcon, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_STATICICON>,   StaticMenuItemIcon<&icons::lock>, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DEBUGTOGGLE>,  ToggleBoolAction, CheckboxIcon, ToggleAccessor>>();
        constructItem<makeComponent<MenuItem, RandomText,                    RandomColor, RandomFont, RandomIcon, DummyAction>>();

        // more scrolling
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DUMMYITEM>,    DummyAction>>();

        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,         SwitchScreenAction<DebugMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
