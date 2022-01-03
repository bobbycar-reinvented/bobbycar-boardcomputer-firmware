#pragma once

#include "actioninterface.h"
#include "utils.h"

using namespace espgui;

namespace {
class SaveSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { saveProfileSettings(); }
};
}
