#pragma once

#include "menuitems/staticswitchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Taccessor, Tvalue Tset, typename Tscreen, const char *Ttext>
class SetValueMenuItem : public StaticSwitchScreenMenuItem<Tscreen, Ttext>
{
    using Base = StaticSwitchScreenMenuItem<Tscreen, Ttext>;

public:
    void triggered() override;
};

template<typename Tvalue, typename Taccessor, Tvalue Tset, typename Tscreen, const char *Ttext>
void SetValueMenuItem<Tvalue, Taccessor, Tset, Tscreen, Ttext>::triggered()
{
    Taccessor::setValue(Tset);

    Base::triggered();
}
}
