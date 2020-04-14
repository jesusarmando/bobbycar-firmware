#pragma once

#include "actioninterface.h"

namespace {
template<typename ...T>
class MultiAction;

template<typename T>
class MultiAction<T> : public virtual ActionInterface
{
public:
    void triggered() override
    {
        m_action.triggered();
    }

private:
    T m_action;
};

template<typename T, typename ...Tmore>
class MultiAction<T, Tmore...> : public virtual MultiAction<Tmore...>
{
public:
    void triggered() override
    {
        m_action.triggered();
        MultiAction<Tmore...>::triggered();
    }

private:
    T m_action;
};
}
