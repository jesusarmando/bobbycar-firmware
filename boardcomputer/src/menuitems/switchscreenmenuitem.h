#pragma once

#include "menuitem.h"
#include "utils.h"

namespace {
template<typename T>
class SwitchScreenItem : public MenuItem
{
public:
    using MenuItem::MenuItem;

    void triggered() const override;
};

template<typename T>
void SwitchScreenItem<T>::triggered() const
{
    switchScreen<T>();
}
}
