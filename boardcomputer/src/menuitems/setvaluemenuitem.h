#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, Tvalue Tset, typename TnextScreen>
class SetValueMenuItem : public SwitchScreenMenuItem<TnextScreen>
{
public:
    SetValueMenuItem(Tvalue &targetValue, const char *text);

    void triggered() const override;

private:
    Tvalue &m_targetValue;
};

template<typename Tvalue, Tvalue Tset, typename TnextScreen>
SetValueMenuItem<Tvalue, Tset, TnextScreen>::SetValueMenuItem(Tvalue &targetValue, const char *text) :
    SwitchScreenMenuItem<TnextScreen>{text},
    m_targetValue{targetValue}
{
}

template<typename Tvalue, Tvalue Tset, typename TnextScreen>
void SetValueMenuItem<Tvalue, Tset, TnextScreen>::triggered() const
{
    m_targetValue = Tset;

    SwitchScreenMenuItem<TnextScreen>::triggered();
}
}
