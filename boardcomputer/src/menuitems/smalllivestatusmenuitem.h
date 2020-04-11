#pragma once

#include "menuitems/livestatusmenuitem.h"

namespace {
template<typename T>
class SmallLiveStatusMenuItem :
    public LiveStatusMenuItem<T>
{
public:
    int font() const override { return 2; }
};
}
