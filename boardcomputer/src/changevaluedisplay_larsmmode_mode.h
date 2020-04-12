#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<>
class ChangeValueDisplay<LarsmMode::Mode> :
    public MenuDisplay,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE1>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE3>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE4>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<LarsmMode::Mode>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    void itemPressed(int index) override;
};

void ChangeValueDisplay<LarsmMode::Mode>::start()
{
    Base::start();

    if (getValue() == LarsmMode::Mode::Mode1)
        setSelectedIndex(0);
    else if (getValue() == LarsmMode::Mode::Mode2)
        setSelectedIndex(1);
    else if (getValue() == LarsmMode::Mode::Mode3)
        setSelectedIndex(2);
    else if (getValue() == LarsmMode::Mode::Mode4)
        setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown LarsmMode::Mode: %i", int(getValue()));
        setSelectedIndex(4);
    }
}

void ChangeValueDisplay<LarsmMode::Mode>::itemPressed(int index)
{
    switch (index)
    {
    case 0: setValue(LarsmMode::Mode::Mode1); break;
    case 1: setValue(LarsmMode::Mode::Mode2); break;
    case 2: setValue(LarsmMode::Mode::Mode3); break;
    case 3: setValue(LarsmMode::Mode::Mode4); break;
    }

    triggered();
}
}
