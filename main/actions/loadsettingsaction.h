#pragma once

#include "actioninterface.h"
#include "utils.h"

using namespace espgui;

namespace {
class LoadSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { loadSettings(); }
};
}
