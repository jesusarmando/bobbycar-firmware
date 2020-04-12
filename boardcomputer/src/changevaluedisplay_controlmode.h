#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<ControlMode> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_OPENMODE>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_VOLTAGE>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SPEED>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_TORQUE>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,     DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<ControlMode>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_OPENMODE>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_VOLTAGE>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SPEED>,    DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_TORQUE>,   DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,     DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<ControlMode>::start()
{
    Base::start();

    if (getValue() == ControlMode::OpenMode)
        setSelectedIndex(0);
    else if (getValue() == ControlMode::Voltage)
        setSelectedIndex(1);
    else if (getValue() == ControlMode::Speed)
        setSelectedIndex(2);
    else if (getValue() == ControlMode::Torque)
        setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown ControlMode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}

void ChangeValueDisplay<ControlMode>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
    {
    case 0: setValue(ControlMode::OpenMode); break;
    case 1: setValue(ControlMode::Voltage); break;
    case 2: setValue(ControlMode::Speed); break;
    case 3: setValue(ControlMode::Torque); break;
    }
}
}
