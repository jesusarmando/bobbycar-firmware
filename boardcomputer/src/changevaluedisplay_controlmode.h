#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<ControlMode> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_OPENMODE>,
        StaticDummyMenuItem<TEXT_VOLTAGE>,
        StaticDummyMenuItem<TEXT_SPEED>,
        StaticDummyMenuItem<TEXT_TORQUE>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<ControlMode>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_OPENMODE>,
        StaticDummyMenuItem<TEXT_VOLTAGE>,
        StaticDummyMenuItem<TEXT_SPEED>,
        StaticDummyMenuItem<TEXT_TORQUE>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<ControlMode>::start()
{
    Base::start();

    if (getValue() == ControlMode::OpenMode)
        Base::setSelectedIndex(0);
    else if (getValue() == ControlMode::Voltage)
        Base::setSelectedIndex(1);
    else if (getValue() == ControlMode::Speed)
        Base::setSelectedIndex(2);
    else if (getValue() == ControlMode::Torque)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown ControlMode: %i", int(getValue()));
        Base::setSelectedIndex(4);
    }
}

void ChangeValueDisplay<ControlMode>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(ControlMode::OpenMode); break;
    case 1: setValue(ControlMode::Voltage); break;
    case 2: setValue(ControlMode::Speed); break;
    case 3: setValue(ControlMode::Torque); break;
    }
}
}
