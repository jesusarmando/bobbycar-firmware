#pragma once

#include <Esp.h>

#include "menuitem.h"

namespace {
class RebootItem final : public MenuItem
{
public:
    RebootItem(const char *text = "Reboot");

    void triggered() const override;
};

RebootItem::RebootItem(const char *text) :
    MenuItem{text}
{
}

void RebootItem::triggered() const
{
    ESP.restart();
}
}
