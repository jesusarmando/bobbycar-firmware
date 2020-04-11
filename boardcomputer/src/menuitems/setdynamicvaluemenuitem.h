#pragma once

#include "menuitems/staticswitchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Tsetter, typename Tgetter, typename Tscreen, const char *Ttext>
class SetDynamicValueMenuItem : public StaticSwitchScreenMenuItem<Tscreen, Ttext>
{
    using Base = StaticSwitchScreenMenuItem<Tscreen, Ttext>;

public:
    void triggered() override;
};

template<typename Tvalue, typename Tsetter, typename Tgetter, typename Tscreen, const char *Ttext>
void SetDynamicValueMenuItem<Tvalue, Tsetter, Tgetter, Tscreen, Ttext>::triggered()
{
    Tsetter::getRef() = Tgetter::getValue();

    Base::triggered();
}
}
