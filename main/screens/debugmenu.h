#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class DebugMenu : public BobbyMenuDisplay
{
public:
    DebugMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
