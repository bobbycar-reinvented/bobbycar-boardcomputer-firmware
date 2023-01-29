#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class GraphsMenu : public BobbyMenuDisplay
{
public:
    GraphsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
