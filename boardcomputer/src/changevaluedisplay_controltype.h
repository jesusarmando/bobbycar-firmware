#pragma once

#include "changevaluedisplay.h"

namespace {
template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<ControlType, Taccessor, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL>,
        SetValueMenuItem<ControlType, Taccessor, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlType, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == ControlType::Commutation)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == ControlType::Sinusoidal)
        Base::setSelectedIndex(1);
    else if (Taccessor::getValue() == ControlType::FieldOrientedControl)
        Base::setSelectedIndex(2);
    else
    {
        Serial.printf("Unknown ControlType: %i", int(Taccessor::getValue()));
        Base::setSelectedIndex(3);
    }
}
}
