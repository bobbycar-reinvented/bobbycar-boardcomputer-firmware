#include "featureflagsmenu.h"

// 3rdparty lib includes
#include <TFT_eSPI.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <fmt/core.h>
#include <icons/back.h>
#include <strutils.h>

// local includes
#include "bobbycheckbox.h"
#include "displays/bobbypopupdisplay.h"
#include "newsettings.h"
#include "taskmanager.h"
#include "bobbyerrorhandler.h"

namespace {
constexpr const char * const TAG = "FEATUREFLAGSMENU";

constexpr char TEXT_FEATUREFLAGS[] = "Feature Flags";
constexpr char TEXT_BACK[] = "Back";
constexpr char TEXT_POPUP[] = "Feature flags have been changed. Please restart the device to apply the changes.";

bool isDirty{false};

class SpecialPopupDisplay : public BobbyPopupDisplay
{
    using Base = BobbyPopupDisplay;
    using Base::Base;
public:
    void buttonPressed(espgui::Button button) override
    {
        //Base::buttonPressed(button);

        switch (button)
        {
            using espgui::Button;
            case Button::Left:
            case Button::Right:
                espgui::popScreen();
                break;
            default:;
        }
    }
};

void exitFeatureFlagsMenu()
{
    if (isDirty)
    {
        using namespace espgui;
        // auto newDisplay = std::make_unique<BobbyPopupDisplay>(, std::move(espgui::displayStack.top()));
        // newDisplay->initOverlay();
        // espgui::currentDisplay = std::move(newDisplay);

        auto newDisplay = std::make_unique<SpecialPopupDisplay>(TEXT_POPUP, std::move(espgui::displayStack.top()));
        newDisplay->initOverlay();
        espgui::currentDisplay = std::move(newDisplay);
    }
    else
        espgui::popScreen();
}

class ExitFeatureFlagsMenuAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        exitFeatureFlagsMenu();
    }
};

class FeatureFlagMenuItem : public espgui::MenuItem, public virtual BobbyErrorHandler {
public:
    explicit FeatureFlagMenuItem(ConfiguredFeatureFlag &flag, bool isInitialized) : m_flag{flag}, m_isInitialized{isInitialized} {}
    std::string text() const override
    {
        std::string_view name = m_flag.isEnabled.nvsName();
        constexpr const std::string_view prefix = "f_";
        if (cpputils::stringStartsWith(name, prefix)) {
            name.remove_prefix(prefix.size());
        }
        std::string return_name = std::string{name};
        return_name += m_flag.isBeta() ? " (beta)" : "";
        return return_name;
    }

    int color() const override
    {
        if (m_isInitialized)
        {
            return m_flag.isBeta() ? TFT_YELLOW : TFT_GREEN;
        }
        else
        {
            if (m_flag.isEnabled.value())
            {
                return TFT_RED;
            }
            else
                return m_flag.isBeta() ? TFT_ORANGE : TFT_GREY;
        }
    }

    void triggered() override
    {
        if (auto result = m_flag.isEnabled.write(configs.nvs_handle_user, !m_flag.isEnabled.value()); !result)
            errorOccured(std::move(result).error());
        else
            isDirty = true;
    }

    const espgui::MenuItemIcon *icon() const override
    {
        return m_flag.isEnabled.value() ? &espgui::icons::checked : &espgui::icons::unchecked;
    }
private:
    ConfiguredFeatureFlag &m_flag;
    const bool m_isInitialized;
};
} // namespace

FeatureFlagsMenu::FeatureFlagsMenu()
{
    using namespace espgui;

    configs.callForEveryFeature([&](ConfiguredFeatureFlag &feature){
        const std::string name = feature.getTaskName();
        if (const auto err = checkInitializedByName(name); err)
        {
            constructMenuItem<FeatureFlagMenuItem>(feature, *err);
        }
        else
            constructMenuItem<FeatureFlagMenuItem>(feature, true);
    });
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, ExitFeatureFlagsMenuAction>>();
}

void FeatureFlagsMenu::start()
{
    Base::start();
    isDirty = false;
}

std::string FeatureFlagsMenu::text() const
{
    return TEXT_FEATUREFLAGS;
}

void FeatureFlagsMenu::back()
{
    exitFeatureFlagsMenu();
}

