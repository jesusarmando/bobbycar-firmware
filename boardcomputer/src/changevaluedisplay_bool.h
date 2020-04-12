#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "actioninterface.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<>
class ChangeValueDisplay<bool> :
    public MenuDisplay,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_TRUE>,  DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_FALSE>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,  DummyAction, StaticMenuItemIcon<&icons::back>>
    >,
    public virtual AccessorInterface<bool>,
    public virtual ActionInterface
{
    using Base = MenuDisplay;

public:
    void start() override;

    void itemPressed(int index) override;
};

void ChangeValueDisplay<bool>::start()
{
    Base::start();

    if (getValue() == true)
        setSelectedIndex(0);
    else if (getValue() == false)
        setSelectedIndex(1);
}

void ChangeValueDisplay<bool>::itemPressed(int index)
{
    switch (index)
    {
    case 0: setValue(true); break;
    case 1: setValue(false); break;
    }

    triggered();
}
}
