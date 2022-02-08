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
#include "bobbyerrorhandler.h"

namespace typesafeenumchangemenu {
constexpr char TEXT_BACK[] = "Back";
} // namespace typesafeenumchangemenu

template<typename TEnum>
class TypesafeEnumCurrentValueMenuItem :
        public espgui::MenuItem
{
public:
    TypesafeEnumCurrentValueMenuItem(const ConfigWrapper<TEnum> &config) : m_config{config} {}
    std::string text() const override
    {
        return toString(m_config.value);
    }
    void triggered() override {}

    int color() const override
    {
        return TFT_DARKGREY;
    }
private:
    const ConfigWrapper<TEnum> &m_config;
};

template<typename TEnum>
class TypesafeEnumSetterMenuItem :
        public espgui::MenuItem
{
public:
    TypesafeEnumSetterMenuItem(TEnum value, const ConfigWrapper<TEnum> &config) : m_value{value}, m_config{config} {}

    std::string text() const override
    {
        return toString(m_value);
    }

    void triggered() override
    {
        if (auto result = configs.write_config(m_config, m_value); !result)
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
    }
private:
    const TEnum m_value;
    const ConfigWrapper<TEnum> &m_config;
};

template<typename TEnum, typename TMenu>
class TypeSafeChangeMenu :
        public BobbyMenuDisplay
{
public:
    TypeSafeChangeMenu(const ConfigWrapper<TEnum> &config) : m_config{config}
    {
        using namespace espgui;
        using namespace typesafeenumchangemenu;
        constructMenuItem<TypesafeEnumCurrentValueMenuItem<TEnum>>(*m_config);
        constructMenuItem<makeComponent<MenuItem, EmptyText, DummyAction>>();
        iterateEnum<TEnum>([&](TEnum enum_value, const auto &string_value){
            constructMenuItem<TypesafeEnumSetterMenuItem<TEnum>>(enum_value, m_config);
        });
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<TMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }

    std::string text() const override
    {
        return fmt::format("Select {}", m_config.nvsName());
    }

    void back() override
    {
        espgui::switchScreen<TMenu>();
    }
private:
    const ConfigWrapper<TEnum> &m_config;
};

template<typename TEnum, typename TMenu, const char *Ttext>
class SwitchScreenTypeSafeChangeMenuItem : public espgui::MenuItem
{
public:
    SwitchScreenTypeSafeChangeMenuItem(const ConfigWrapper<TEnum> &config) : m_config{config} {}

    static constexpr const char *STATIC_TEXT = Ttext;
    std::string text() const override
    {
        return Ttext;
    }

    void triggered() override
    {
        espgui::switchScreen<TypeSafeChangeMenu<TEnum, TMenu>>(*m_config);
    }
private:
    const ConfigWrapper<TEnum> &m_config;
};
