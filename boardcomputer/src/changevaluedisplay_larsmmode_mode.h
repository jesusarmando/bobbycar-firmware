#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<>
class ChangeValueDisplay<LarsmMode::Mode> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE1>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE2>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE3>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE4>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<LarsmMode::Mode>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE1>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE2>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE3>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODE4>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >;

public:
    void start() override;

    void triggered() override;
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

void ChangeValueDisplay<LarsmMode::Mode>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
    {
    case 0: setValue(LarsmMode::Mode::Mode1); break;
    case 1: setValue(LarsmMode::Mode::Mode2); break;
    case 2: setValue(LarsmMode::Mode::Mode3); break;
    case 3: setValue(LarsmMode::Mode::Mode4); break;
    }
}
}
