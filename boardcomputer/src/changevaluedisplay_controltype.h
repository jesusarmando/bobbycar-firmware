#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<ControlType> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_COMMUTATION>,          DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SINUSOIDAL>,           DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FIELDORIENTEDCONTROL>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 DefaultFont, DefaultColor, DummyAction>
    >,
    public virtual AccessorInterface<ControlType>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_COMMUTATION>,          DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SINUSOIDAL>,           DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FIELDORIENTEDCONTROL>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                 DefaultFont, DefaultColor, DummyAction>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<ControlType>::start()
{
    Base::start();

    if (getValue() == ControlType::Commutation)
        setSelectedIndex(0);
    else if (getValue() == ControlType::Sinusoidal)
        setSelectedIndex(1);
    else if (getValue() == ControlType::FieldOrientedControl)
        setSelectedIndex(2);
    else
    {
        Serial.printf("Unknown ControlType: %i", int(getValue()));
        setSelectedIndex(3);
    }
}

void ChangeValueDisplay<ControlType>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
    {
    case 0: setValue(ControlType::Commutation); break;
    case 1: setValue(ControlType::Sinusoidal); break;
    case 2: setValue(ControlType::FieldOrientedControl); break;
    }
}
}
