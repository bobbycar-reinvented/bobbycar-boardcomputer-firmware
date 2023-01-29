#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class BuzzerMenu : public BobbyMenuDisplay
{
public:
    BuzzerMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
