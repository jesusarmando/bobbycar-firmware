#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, Tvalue Tset, typename TnextScreen>
class SetValueMenuItem : public SwitchScreenItem<TnextScreen>
{
public:
    SetValueMenuItem(Tvalue &currentValue, const char *text);

    void triggered() const override;

private:
    Tvalue &m_currentValue;
};

template<typename Tvalue, Tvalue Tset, typename TnextScreen>
SetValueMenuItem<Tvalue, Tset, TnextScreen>::SetValueMenuItem(Tvalue &currentValue, const char *text) :
    SwitchScreenItem<TnextScreen>{text},
    m_currentValue{currentValue}
{
}

template<typename Tvalue, Tvalue Tset, typename TnextScreen>
void SetValueMenuItem<Tvalue, Tset, TnextScreen>::triggered() const
{
    m_currentValue = Tset;

    SwitchScreenItem<TnextScreen>::triggered();
}
}
