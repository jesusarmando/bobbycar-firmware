#pragma once

#include "actioninterface.h"
#include "globals.h"

namespace {
class SaveSettingsAction : public virtual ActionInterface
{
public:
    void triggered() override { settingsSaver.save(settings); }
};
}
