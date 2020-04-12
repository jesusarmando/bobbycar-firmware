#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "menuitems/staticdummymenuitem.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<bool> :
    public StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_TRUE>,
        StaticDummyMenuItem<TEXT_FALSE>,
        StaticDummyMenuItem<TEXT_BACK>
    >,
    public virtual AccessorInterface<bool>
{
    using Base = StaticMenuDisplay<
        StaticDummyMenuItem<TEXT_TRUE>,
        StaticDummyMenuItem<TEXT_FALSE>,
        StaticDummyMenuItem<TEXT_BACK>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<bool>::start()
{
    Base::start();

    if (getValue() == true)
        Base::setSelectedIndex(0);
    else if (getValue() == false)
        Base::setSelectedIndex(1);
}

void ChangeValueDisplay<bool>::triggered()
{
    Base::triggered();

    switch (Base::selectedIndex())
    {
    case 0: setValue(true); break;
    case 1: setValue(false); break;
    }
}
}
