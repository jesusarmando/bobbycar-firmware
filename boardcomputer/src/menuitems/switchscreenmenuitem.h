#pragma once

#include "menuitems/menuitem.h"
#include "actions/switchscreenaction.h"

namespace {
template<typename Tscreen>
class SwitchScreenMenuItem :
    public MenuItem,
    public virtual SwitchScreenAction<Tscreen>
{};
}
