#pragma once

// local includes
#include "textinterface.h"

namespace bobby {

struct CloudCreatedText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

struct CloudStartedText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

struct CloudConnectedText : public virtual espgui::TextInterface
{
public:
    std::string text() const override;
};

} // namespace bobby
