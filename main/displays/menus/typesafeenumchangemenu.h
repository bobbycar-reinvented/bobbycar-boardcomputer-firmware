#pragma once

// 3rdparty lib includes
#include <configwrapper.h>
#include <fmt/core.h>
#include <icons/back.h>

// local includes
#include "globals.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "displays/bobbymenudisplay.h"

namespace typesafeenumchangemenu {
constexpr char TEXT_BACK[] = "Back";
} // namespace typesafeenumchangemenu

template<typename TEnum, espconfig::ConfigWrapper<TEnum> config>
class TypesafeEnumCurrentValueMenuItemText :
        public espgui::TextInterface
{
    std::string text() const override
    {
        return toString(config.value);
    }
};

template<typename TEnum, espconfig::ConfigWrapper<TEnum> config>
class TypesafeEnumSetterMenuItem :
        public espgui::MenuItem
{
    std::string text() const override
    {
        return toString(config.value);
    }

    void triggered() override
    {

    }
};

template<typename TEnum, typename TMenu, espconfig::ConfigWrapper<TEnum> config>
class TypeSafeChangeMenu :
        public BobbyMenuDisplay
{
    TypeSafeChangeMenu()
    {
        using namespace espgui;
        using namespace typesafeenumchangemenu;
        constructMenuItem<makeComponent<MenuItem, TypesafeEnumCurrentValueMenuItemText<TEnum, config>, DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, EmptyText, DummyAction>>();
        iterate([&](TEnum enum_value, const auto &string_value){ // this line needs to be fixed, help required
            constructMenuItem<TypesafeEnumSetterMenuItem<TEnum, config>>(enum_value);
        });
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<TMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
\
    std::string text() const override
    {
        return fmt::format("Select {}", config.nvsName());
    }
\
    void back() override
    {
        espgui::switchScreen<TMenu>();
    }
};
