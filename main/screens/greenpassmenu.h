#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class GreenPassMenu : public BobbyMenuDisplay
{
public:
    GreenPassMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
