#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class InvertMenu : public BobbyMenuDisplay
{
public:
    InvertMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
