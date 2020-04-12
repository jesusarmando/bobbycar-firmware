#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"
#include "modes/larsmmode.h"

namespace {
template<>
class ChangeValueDisplay<LarsmMode::Mode> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_LARSMMODE1>,
        StaticDummyMenuItem<TEXT_LARSMMODE2>,
        StaticDummyMenuItem<TEXT_LARSMMODE3>,
        StaticDummyMenuItem<TEXT_LARSMMODE4>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<LarsmMode::Mode>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_LARSMMODE1>,
        StaticDummyMenuItem<TEXT_LARSMMODE2>,
        StaticDummyMenuItem<TEXT_LARSMMODE3>,
        StaticDummyMenuItem<TEXT_LARSMMODE4>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<LarsmMode::Mode>::start()
{
    Base::start();

    if (getValue() == LarsmMode::Mode::Mode1)
        Base::setSelectedIndex(0);
    else if (getValue() == LarsmMode::Mode::Mode2)
        Base::setSelectedIndex(1);
    else if (getValue() == LarsmMode::Mode::Mode3)
        Base::setSelectedIndex(2);
    else if (getValue() == LarsmMode::Mode::Mode4)
        Base::setSelectedIndex(3);
    else
    {
        Serial.printf("Unknown LarsmMode::Mode: %i", int(getValue()));
        Base::setSelectedIndex(4);
    }
}

void ChangeValueDisplay<LarsmMode::Mode>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(LarsmMode::Mode::Mode1); break;
    case 1: setValue(LarsmMode::Mode::Mode2); break;
    case 2: setValue(LarsmMode::Mode::Mode3); break;
    case 3: setValue(LarsmMode::Mode::Mode4); break;
    }
}
}
