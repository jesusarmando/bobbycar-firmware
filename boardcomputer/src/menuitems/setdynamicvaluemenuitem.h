#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Tsetter, typename Tgetter, typename Tscreen, const char *Ttext>
class SetDynamicValueMenuItem : public SwitchScreenMenuItem<Tscreen, Ttext>
{
public:
    void triggered() override;
};

template<typename Tvalue, typename Tsetter, typename Tgetter, typename Tscreen, const char *Ttext>
void SetDynamicValueMenuItem<Tvalue, Tsetter, Tgetter, Tscreen, Ttext>::triggered()
{
    Tsetter::getRef() = Tgetter::getValue();

    SwitchScreenMenuItem<Tscreen, Ttext>::triggered();
}
}
