#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename Tvalue, typename Tscreen, const char *Ttext>
class SetDynamicValueMenuItem : public SwitchScreenMenuItem<Tscreen, Ttext>
{
public:
    SetDynamicValueMenuItem(Tvalue &targetValue, Tvalue value);

    void triggered() const override;

private:
    Tvalue &m_targetValue;
    const Tvalue m_value;
};

template<typename Tvalue, typename Tscreen, const char *Ttext>
SetDynamicValueMenuItem<Tvalue, Tscreen, Ttext>::SetDynamicValueMenuItem(Tvalue &targetValue, Tvalue value) :
    m_targetValue{targetValue},
    m_value{value}
{
}

template<typename Tvalue, typename Tscreen, const char *Ttext>
void SetDynamicValueMenuItem<Tvalue, Tscreen, Ttext>::triggered() const
{
    m_targetValue = m_value;

    SwitchScreenMenuItem<Tscreen, Ttext>::triggered();
}
}
