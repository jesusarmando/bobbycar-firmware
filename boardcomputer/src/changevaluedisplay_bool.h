#pragma once

#include "changevaluedisplay.h"
#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<bool> :
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_TRUE>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FALSE>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,  DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<bool>
{
    using Base = StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_TRUE>,  DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FALSE>, DefaultFont, DefaultColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,  DefaultFont, DefaultColor, DummyAction, StaticMenuItemIcon<&icons::back>>
    >;

public:
    void start() override;

    void triggered() override;
};

void ChangeValueDisplay<bool>::start()
{
    Base::start();

    if (getValue() == true)
        setSelectedIndex(0);
    else if (getValue() == false)
        setSelectedIndex(1);
}

void ChangeValueDisplay<bool>::triggered()
{
    Base::triggered();

    switch (selectedIndex())
    {
    case 0: setValue(true); break;
    case 1: setValue(false); break;
    }
}
}
