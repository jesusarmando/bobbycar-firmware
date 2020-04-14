#pragma once

#include "actioninterface.h"
#include "globals.h"

namespace {
class LoadSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { settingsSaver.load(settings); }
};
}
