#pragma once

#include "switchscreenmenuitem.h"

namespace {
template<typename T>
class SetValueMenuItem : public SwitchScreenItem
{
public:
    SetValueMenuItem(T newValue, T &currentValue, Display &display, const char *text);

    void triggered() const override;

private:
    const T m_newValue;
    T &m_currentValue;
};

template<typename T>
SetValueMenuItem<T>::SetValueMenuItem(T newValue, T &currentValue, Display &display, const char *text) :
    SwitchScreenItem{display, text},
    m_newValue{newValue},
    m_currentValue{currentValue}
{
}

template<typename T>
void SetValueMenuItem<T>::triggered() const
{
    m_currentValue = m_newValue;

    SwitchScreenItem::triggered();
}
}
