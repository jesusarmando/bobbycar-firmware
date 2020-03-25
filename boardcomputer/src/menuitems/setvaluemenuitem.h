#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Taccessor, Tvalue Tset, typename Tscreen, const char *Ttext>
class SetValueMenuItem : public SwitchScreenMenuItem<Tscreen, Ttext>
{
public:
    void triggered() const override;
};

template<typename Tvalue, typename Taccessor, Tvalue Tset, typename Tscreen, const char *Ttext>
void SetValueMenuItem<Tvalue, Taccessor, Tset, Tscreen, Ttext>::triggered() const
{
    Taccessor::setValue(Tset);

    SwitchScreenMenuItem<Tscreen, Ttext>::triggered();
}
}
