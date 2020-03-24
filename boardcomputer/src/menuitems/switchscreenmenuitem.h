#pragma once

#include "menuitem.h"
#include "utils.h"

namespace {
template<typename T>
class SwitchScreenMenuItem : public MenuItem
{
public:
    using MenuItem::MenuItem;

    void triggered() const override;
};

template<typename T>
void SwitchScreenMenuItem<T>::triggered() const
{
    switchScreen<T>();
}
}
