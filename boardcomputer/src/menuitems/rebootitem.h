#pragma once

#include <Esp.h>

#include "menuitem.h"

namespace {
class RebootItem final : public MenuItem
{
public:
    RebootItem();

    void triggered() const override;
};

RebootItem::RebootItem() :
    MenuItem{"Reboot"}
{
}

void RebootItem::triggered() const
{
    ESP.restart();
}
}
