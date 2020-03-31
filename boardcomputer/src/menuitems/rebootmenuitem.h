#pragma once

#include <Esp.h>

#include "menuitem.h"

namespace {
template<const char *Ttext>
class RebootMenuItem final : public MenuItem<Ttext>
{
public:
    void triggered() const override;
};

template<const char *Ttext>
void RebootMenuItem<Ttext>::triggered() const
{
    ESP.restart();
}
}
