#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <textinterface.h>
#include <espchrono.h>

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class RandomTitle : public virtual espgui::TitleInterface
{
public:
    std::string title() const override;

private:
    mutable std::optional<espchrono::millis_clock::time_point> m_nextUpdate;
    mutable std::string m_title;
};

class RandomText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;

private:
    mutable std::optional<espchrono::millis_clock::time_point> m_nextUpdate;
    mutable std::string m_text;
};

class DynamicDebugMenu :
    public BobbyMenuDisplay,
    public RandomTitle
{
public:
    DynamicDebugMenu();

    void back() override;
};

} // namespace bobby
