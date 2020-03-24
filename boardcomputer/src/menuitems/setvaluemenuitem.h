#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, Tvalue Tset, typename Tscreen, const char *Ttext>
class SetValueMenuItem : public SwitchScreenMenuItem<Tscreen, Ttext>
{
public:
    SetValueMenuItem(Tvalue &targetValue);

    void triggered() const override;

private:
    Tvalue &m_targetValue;
};

template<typename Tvalue, Tvalue Tset, typename Tscreen, const char *Ttext>
SetValueMenuItem<Tvalue, Tset, Tscreen, Ttext>::SetValueMenuItem(Tvalue &targetValue) :
    m_targetValue{targetValue}
{
}

template<typename Tvalue, Tvalue Tset, typename Tscreen, const char *Ttext>
void SetValueMenuItem<Tvalue, Tset, Tscreen, Ttext>::triggered() const
{
    m_targetValue = Tset;

    SwitchScreenMenuItem<Tscreen, Ttext>::triggered();
}
}
