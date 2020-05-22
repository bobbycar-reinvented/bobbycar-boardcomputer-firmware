#pragma once

#include <utility>

#include "menuitem.h"

namespace {
class MenuDefinitionInterface
{
public:
    virtual void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) = 0;
    virtual void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const = 0;
};
}
