#pragma once

#include <Esp.h>

#include "menuitem.h"

namespace {
constexpr char TEXT_REBOOT[] = "Reboot";
class RebootItem final : public MenuItem<TEXT_REBOOT>
{
public:
    void triggered() const override;
};

void RebootItem::triggered() const
{
    ESP.restart();
}
}
