#include "manageprofilesmenu.h"

// 3rdparty lib includes
#include <icons/back.h>
#include <TFT_eSPI.h>

// local includes
#include "actions/switchscreenaction.h"
#include "bobbyerrorhandler.h"
#include "globals.h"
#include "mainmenu.h"
#include "presets.h"
#include "utils.h"

constexpr const char * const TAG = "ProfileManager";

using namespace espgui;

namespace  {
constexpr char TEXT_MANAGEPROFILESMENU[] = "Manage Profiles Menu";
constexpr char TEXT_BACK[] = "Back";
} // namespace

class ManageProfileMenuItem : public MenuItem
{
    using Base = MenuItem;
public:
    ManageProfileMenuItem(ManageProfilesMenu &menu, const uint8_t profileIndex) : m_menu{menu}, m_profileIndex{profileIndex} {}
    void copy()
    {

    }

    void swap()
    {

    }

    void clear()
    {
        if (m_mode == CONFIRMCLEAR)
        {
            m_menu.unlock();
            ESP_LOGI(TAG, "Reseting profile %i...", m_profileIndex);
            profileSettings = presets::defaultProfileSettings;
            m_mode = _DEFAULT;
        }
        else
        {
            m_menu.lock();
            m_mode = CONFIRMCLEAR;
            BobbyErrorHandler{}.errorOccured("Press CONFIRM to reset Profile or BACK to cancel.");
        }
    }

    std::string text() const override
    {
        switch (m_mode)
        {
        case _DEFAULT:
            return fmt::format("Profile {}", m_profileIndex);
        case CONFIRMCLEAR:
            return fmt::format("&1Profile {}", m_profileIndex);
        }
        return fmt::format("Profile {}", m_profileIndex);
    }

    int color() const override
    {
        if (m_mode == CONFIRMCLEAR)
            return TFT_RED;
        else if (m_menu.m_locked)
            return TFT_DARKGREY;
        return TFT_WHITE;
    };

    void triggered() override
    {
        switch (m_menu.m_action)
        {
        case Actions::Clear:
            clear();
            break;
        case Actions::Copy:
            copy();
            break;
        case Actions::Swap:
            swap();
            break;
        default:
            break;
        }
    }

    void update() override
    {
        Base::update();
        if (m_mode != _DEFAULT && !m_menu.m_locked)
            m_mode = _DEFAULT;
    }
private:
    enum Mode : uint8_t {
        _DEFAULT,
        CONFIRMCLEAR
    } m_mode;
    ManageProfilesMenu &m_menu;
    const uint8_t m_profileIndex;
};

class ManageProfileModeMenuItem : public MenuItem
{
public:
    ManageProfileModeMenuItem(ManageProfilesMenu &menu) : m_menu{menu} {}
    std::string text() const override {
        return fmt::format("&7{}", m_menu.action_text());
    }

    void triggered() override {
        m_menu.m_action = Actions((uint8_t)m_menu.m_action+1);

        if(m_menu.m_action == Actions::__END__)
        {
            m_menu.m_action = Actions(0);
        }
    }
private:
    ManageProfilesMenu &m_menu;
};

ManageProfilesMenu::ManageProfilesMenu()
{
    for (uint8_t i = 0; i < 4; i++)
    {
       constructMenuItem<ManageProfileMenuItem>(*this, i);
    }
    constructMenuItem<ManageProfileModeMenuItem>(*this);
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void ManageProfilesMenu::start()
{
    Base::start();
    m_oldMode = currentMode;
    currentMode = &m_mode;
}

void ManageProfilesMenu::stop()
{
    Base::stop();

    if (currentMode == &m_mode)
    {
        m_mode.stop();
        lastMode = nullptr;
        currentMode = m_oldMode;
    }
}

void ManageProfilesMenu::back()
{
    if (!m_locked)
        switchScreen<MainMenu>();
    else
        m_locked = false;
}

std::string ManageProfilesMenu::text() const
{
    return TEXT_MANAGEPROFILESMENU;
}

std::string ManageProfilesMenu::action_text() const {
    return toString(m_action);
}

void ManageProfilesMenu::lock() {
    m_locked = true;
}

void ManageProfilesMenu::unlock() {
    m_locked = false;
}
// functions: clear profile, copy profile, move profile
// TODO: If m_locked == true, only confirm and back (espgui::Button::Right and espgui::Button::Left) should be allowed to pass to the menuitems.
//
