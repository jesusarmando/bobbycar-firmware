#pragma once

#include "modebase.h"

namespace {
class WebsocketMode final : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override {};

    const char *displayName() const override { return "Websocket"; }
};

namespace modes {
WebsocketMode websocketMode;
}
}
