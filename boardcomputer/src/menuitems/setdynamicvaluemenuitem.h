#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename TnextScreen>
class SetDynamicValueMenuItem : public SwitchScreenMenuItem<TnextScreen>
{
public:
    SetDynamicValueMenuItem(Tvalue &targetValue, Tvalue value, const char *text);

    void triggered() const override;

private:
    Tvalue &m_targetValue;
    const Tvalue m_value;
};

template<typename Tvalue, typename TnextScreen>
SetDynamicValueMenuItem<Tvalue, TnextScreen>::SetDynamicValueMenuItem(Tvalue &targetValue, Tvalue value, const char *text) :
    SwitchScreenMenuItem<TnextScreen>{text},
    m_targetValue{targetValue},
    m_value{value}
{
}

template<typename Tvalue, typename TnextScreen>
void SetDynamicValueMenuItem<Tvalue, TnextScreen>::triggered() const
{
    m_targetValue = m_value;

    SwitchScreenMenuItem<TnextScreen>::triggered();
}
}
