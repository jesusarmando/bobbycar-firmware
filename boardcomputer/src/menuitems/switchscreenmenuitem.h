#pragma once

#include "menuitem.h"
#include "utils.h"

namespace {
template<typename Tscreen>
class SwitchScreenMenuItem : public MenuItem
{
public:
    void triggered() override;
};

template<typename Tscreen>
void SwitchScreenMenuItem<Tscreen>::triggered()
{
    switchScreen<Tscreen>();
}
}
