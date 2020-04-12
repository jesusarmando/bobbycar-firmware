#pragma once

#include "switchscreenmenuitem.h"
#include "titleinterface.h"

namespace {
template<typename Tscreen, const char *Ttext>
class StaticSwitchScreenMenuItem :
    public SwitchScreenMenuItem<Tscreen>,
    public StaticTitle<Ttext>
{};
}
