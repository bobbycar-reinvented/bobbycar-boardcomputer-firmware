#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class EnableMenu : public BobbyMenuDisplay
{
public:
    EnableMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
