#pragma once

#include "changevaluedisplay.h"

namespace {
template<typename Taccessor, typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext> final :
    public StaticTitle<Ttext>,
    public StaticMenuDisplay<
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >
{
    using Base = StaticMenuDisplay<
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Speed, Tdisplay, TEXT_SPEED>,
        SetValueMenuItem<ControlMode, Taccessor, ControlMode::Torque, Tdisplay, TEXT_TORQUE>,
        StaticSwitchScreenMenuItem<Tdisplay, TEXT_BACK>
    >;

public:
    void start() override;
};

template<typename Taccessor, typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlMode, Taccessor, Tdisplay, Ttext>::start()
{
    Base::start();

    if (Taccessor::getValue() == ControlMode::OpenMode)
        Base::setSelectedIndex(0);
    else if (Taccessor::getValue() == ControlMode::Voltage)
        Base::setSelectedIndex(1);
    else if (Taccessor::getValue() == ControlMode::Speed)
        Base::setSelectedIndex(2);
    else if (Taccessor::getValue() == ControlMode::Torque)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown ControlMode: %i", int(Taccessor::getValue()));
        Base::setSelectedIndex(4);
    }
}
}
