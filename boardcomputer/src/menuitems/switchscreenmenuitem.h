#pragma once

#include "menuitem.h"
#include "utils.h"

namespace {
template<typename Tscreen, const char *Ttext>
class SwitchScreenMenuItem : public MenuItem<Ttext>
{
public:
    using MenuItem<Ttext>::MenuItem;

    void triggered() override;
};

template<typename Tscreen, const char *Ttext>
void SwitchScreenMenuItem<Tscreen, Ttext>::triggered()
{
    switchScreen<Tscreen>();
}
}
