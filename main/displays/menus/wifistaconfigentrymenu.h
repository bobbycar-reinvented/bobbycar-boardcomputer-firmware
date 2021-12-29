#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class WifiStaConfigEntryMenu : public BobbyMenuDisplay
{
public:
    WifiStaConfigEntryMenu(int index);

    std::string text() const override;
    void back() override;

private:
    const int m_index;
};
