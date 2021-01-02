#pragma once

// system includes
#include <vector>
#include <memory>

// local includes
#include "menudefinitioninterface.h"

namespace {
class ContainerMenuDefinition : public virtual MenuDefinitionInterface
{
public:
    std::size_t size() const override { return m_items.size(); }

    MenuItem& getMenuItem(std::size_t index) override
    {
        if (index < m_items.size())
            return *m_items[index].get();

        throw "aua";
    }

    const MenuItem& getMenuItem(std::size_t index) const override
    {
        if (index < m_items.size())
            return *m_items[index].get();

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        for (const auto &ptr : m_items)
            callback(*ptr);
    }

    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        for (const auto &ptr : m_items)
            callback(*ptr);
    }

    template<typename T, typename... Args>
    T &constructItem(Args&&... args)
    {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T &ref = *ptr;
        emplaceItem(std::move(ptr));
        return ref;
    }

    void emplaceItem(std::unique_ptr<MenuItem> &&ptr)
    {
        m_items.emplace_back(std::move(ptr));
    }

    void clearItems()
    {
        m_items.clear();
    }

    std::unique_ptr<MenuItem> takeLast()
    {
        if (m_items.empty())
            throw "aua";

        std::unique_ptr<MenuItem> ptr = std::move(m_items.back());
        m_items.pop_back();
        return ptr;
    }

private:
    std::vector<std::unique_ptr<MenuItem>> m_items;
};
} // namespace
