#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class SelectBuildServerMenu : public BobbyMenuDisplay
{
public:
    SelectBuildServerMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
