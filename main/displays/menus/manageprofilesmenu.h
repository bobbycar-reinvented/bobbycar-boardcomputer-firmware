#pragma once

// 3rdparty lib includes
#include <cpptypesafeenum.h>

// local includes
#include "displays/bobbymenudisplay.h"
#include "modes/ignoreinputmode.h"

#define ActionValues(x) \
    x(Clear) \
    x(Copy) \
    x(Swap) \
    x(__END__)
DECLARE_TYPESAFE_ENUM(Actions, : uint8_t, ActionValues)

class ManageProfilesMenu : public BobbyMenuDisplay
{
    friend class ManageProfileMenuItem;
    friend class ManageProfileModeMenuItem;
    using Base = BobbyMenuDisplay;
public:
    ManageProfilesMenu();
    void start() override;
    void stop() override;

    std::string text() const override;
    std::string action_text() const;
    void back() override;
    void lock();
    void unlock();
private:
    ModeInterface *m_oldMode;
    IgnoreInputMode m_mode{0, bobbycar::protocol::ControlType::FieldOrientedControl, bobbycar::protocol::ControlMode::Torque};
protected:
    bool m_locked{false};
    Actions m_action{Actions::Clear};
};
