#pragma once

#include "menuitems/switchscreenmenuitem.h"
#include "titleinterface.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BackMenuItem :
    public SwitchScreenMenuItem<Tscreen>,
    public StaticTitle<TEXT_BACK>
{};
}
