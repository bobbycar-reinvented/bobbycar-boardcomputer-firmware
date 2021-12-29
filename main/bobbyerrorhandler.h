#pragma once

// 3rdparty lib includes
#include <errorhandlerinterface.h>

struct BobbyErrorHandler : public virtual espgui::ErrorHandlerInterface
{
    void errorOccured(std::string &&error) override;
};
