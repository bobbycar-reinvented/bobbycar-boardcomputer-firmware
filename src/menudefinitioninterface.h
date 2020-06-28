#pragma once

#include <utility>

#include "menuitem.h"

namespace {
class MenuDefinitionInterface
{
public:
    virtual std::size_t size() const = 0;

    virtual MenuItem& getMenuItem(std::size_t index) = 0;
    virtual const MenuItem& getMenuItem(std::size_t index) const = 0;

    virtual void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) = 0;
    virtual void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const = 0;
};
}
