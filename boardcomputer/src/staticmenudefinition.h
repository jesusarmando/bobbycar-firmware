#pragma once

#include "menudefinitioninterface.h"

namespace {
template<typename ...T>
class StaticMenuDefinition;

template<typename T>
class StaticMenuDefinition<T> : public virtual MenuDefinitionInterface
{
public:
    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
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
    void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) override
    {
        callback(item);
        Base::runForEveryMenuItem(std::move(callback));
    }

private:
    T item;
};
}
