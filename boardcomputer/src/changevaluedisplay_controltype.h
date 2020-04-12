#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<ControlType> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_COMMUTATION>,
        StaticDummyMenuItem<TEXT_SINUSOIDAL>,
        StaticDummyMenuItem<TEXT_FIELDORIENTEDCONTROL>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<ControlType>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_COMMUTATION>,
        StaticDummyMenuItem<TEXT_SINUSOIDAL>,
        StaticDummyMenuItem<TEXT_FIELDORIENTEDCONTROL>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<ControlType>::start()
{
    Base::start();

    if (getValue() == ControlType::Commutation)
        Base::setSelectedIndex(0);
    else if (getValue() == ControlType::Sinusoidal)
        Base::setSelectedIndex(1);
    else if (getValue() == ControlType::FieldOrientedControl)
        Base::setSelectedIndex(2);
    else
    {
        Serial.printf("Unknown ControlType: %i", int(getValue()));
        Base::setSelectedIndex(3);
    }
}

void ChangeValueDisplay<ControlType>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(ControlType::Commutation); break;
    case 1: setValue(ControlType::Sinusoidal); break;
    case 2: setValue(ControlType::FieldOrientedControl); break;
    }
}
}
