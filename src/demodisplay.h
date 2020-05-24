#pragma once

#include "actioninterface.h"
#include "display.h"

namespace {
class DemoDisplay : public Display, public virtual ActionInterface
{
public:
    void confirm() override;
};

void DemoDisplay::confirm()
{
    triggered();
}
}
