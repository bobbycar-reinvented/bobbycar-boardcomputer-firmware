#pragma once

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <configwrapper.h>
#include <fmt/core.h>

// local includes
#include "globals.h"
#include "guihelpers/bobbyerrorhandler.h"
#include "guihelpers/bobbymenudisplay.h"
#include "icons/back.h"
#include "icons/back_grey.h"

namespace bobby {

namespace typesafeenumchangemenu {
constexpr char TEXT_BACK[] = "Back";

template<typename TEnum>
class TypesafeEnumCurrentValueMenuItem :
        public espgui::MenuItem
{
public:
    explicit TypesafeEnumCurrentValueMenuItem(ConfigWrapper<TEnum>* config) : m_config{config} {}
    std::string text() const override
    {
        return toString(m_config->value());
    }
    void triggered() override {}

    int color() const override
    {
        return espgui::TFT_DARKGREY;
    }
private:
    ConfigWrapper<TEnum>* m_config;
};

template<typename TEnum>
class TypesafeEnumSetterMenuItem final :
        public espgui::MenuItem
{
public:
    TypesafeEnumSetterMenuItem(TEnum value, ConfigWrapper<TEnum>* config) : m_value{value}, m_config{config} {}

    std::string text() const override
    {
        return toString(m_value);
    }

    void triggered() override
    {
        if (auto result = m_config->write(configs.nvs_handle_user, m_value); !result)
            BobbyErrorHandler{}.errorOccurred(std::move(result).error());
    }
private:
    TEnum m_value;
    ConfigWrapper<TEnum>* m_config;
};

template<typename TEnum>
class TypeSafeChangeMenu final :
        public BobbyMenuDisplay
{
public:
    explicit TypeSafeChangeMenu(ConfigWrapper<TEnum>* config) : m_config{config}
    {
        using namespace espgui;
        using namespace typesafeenumchangemenu;
        constructMenuItem<TypesafeEnumCurrentValueMenuItem<TEnum>>(m_config);
        iterateEnum<TEnum>::iterate([&](TEnum enum_value, const auto &string_value){
            constructMenuItem<TypesafeEnumSetterMenuItem<TEnum>>(enum_value, m_config);
        });
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
    }

    std::string title() const override
    {
        return fmt::format("Select {}", m_config->nvsName());
    }

    void back() override
    {
        espgui::popScreen();
    }
private:
    ConfigWrapper<TEnum>* m_config;
};
} // namespace typesafeenumchangemenu

template<typename TEnum, const char *Ttext>
class SwitchScreenTypeSafeChangeMenuItem final : public espgui::MenuItem
{
public:
    explicit SwitchScreenTypeSafeChangeMenuItem(ConfigWrapper<TEnum>* config) : m_config{config} {}

    static constexpr const char *STATIC_TEXT = Ttext;
    std::string text() const override
    {
        return Ttext;
    }

    void triggered() override
    {
        espgui::pushScreen<typesafeenumchangemenu::TypeSafeChangeMenu<TEnum>>(m_config);
    }
private:
    ConfigWrapper<TEnum>* m_config;
};

template<typename TEnum, const char *Ttext>
class PopScreenTypeSafeChangeMenuItem final : public espgui::MenuItem
{
public:
    explicit PopScreenTypeSafeChangeMenuItem(ConfigWrapper<TEnum>* config) : m_config{config} {}

    static constexpr const char *STATIC_TEXT = Ttext;
    std::string text() const override
    {
        return Ttext;
    }

    void triggered() override
    {
        espgui::popScreen();
    }
private:
    ConfigWrapper<TEnum>* m_config;
};

template<typename TEnum, const char *Ttext>
class PushScreenTypeSafeChangeMenuItem final : public espgui::MenuItem
{
public:
    explicit PushScreenTypeSafeChangeMenuItem(ConfigWrapper<TEnum>* config) : m_config{config} {}

    static constexpr const char *STATIC_TEXT = Ttext;
    std::string text() const override
    {
        return Ttext;
    }

    void triggered() override
    {
        espgui::pushScreen<typesafeenumchangemenu::TypeSafeChangeMenu<TEnum>>(m_config);
    }
private:
    ConfigWrapper<TEnum>* m_config;
};

} // namespace bobby
