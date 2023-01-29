#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class DemosMenu : public BobbyMenuDisplay
{
public:
    DemosMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
