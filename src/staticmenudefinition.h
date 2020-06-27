#pragma once

#include "menudefinitioninterface.h"

namespace {
template<typename ...T>
class StaticMenuDefinition;

template<typename T>
class StaticMenuDefinition<T> : public virtual MenuDefinitionInterface
{
public:
    std::size_t size() const override { return 1; }

    MenuItem& getMenuItem(std::size_t index) override
    {
        if (index == 0)
            return item;

        throw "aua";
    }

    const MenuItem& getMenuItem(std::size_t index) const override
    {
        if (index == 0)
            return item;

        throw "aua";
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(item);
    }

    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(item);
    }

private:
    T item;
};

template<typename T, typename ...Tmore>
class StaticMenuDefinition<T, Tmore...> : public virtual StaticMenuDefinition<Tmore...>
{
    using Base = StaticMenuDefinition<Tmore...>;

public:
    std::size_t size() const override { return 1 + sizeof...(Tmore); }

    MenuItem& getMenuItem(std::size_t index) override
    {
        if (index == 0)
            return item;

        return Base::getMenuItem(index - 1);
    }

    const MenuItem& getMenuItem(std::size_t index) const override
    {
        if (index == 0)
            return item;

        return Base::getMenuItem(index - 1);
    }

    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(item);
        Base::runForEveryMenuItem(std::move(callback));
    }

    void runForEveryMenuItem(std::function<void(const MenuItem&)> &&callback) const override
    {
        callback(item);
        Base::runForEveryMenuItem(std::move(callback));
    }

private:
    T item;
};
}
