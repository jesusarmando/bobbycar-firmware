#pragma once

#include "modes/modeinterface.h"

namespace {
class WebsocketMode final : public ModeInterface
{
public:
    using ModeInterface::ModeInterface;

    void update() override {};

    const char *displayName() const override { return "Websocket"; }
};

namespace modes {
WebsocketMode websocketMode;
}
}
