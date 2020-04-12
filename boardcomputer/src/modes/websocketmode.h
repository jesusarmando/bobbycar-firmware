#pragma once

#include "modeinterface.h"

namespace {
class WebsocketMode : public ModeInterface
{
public:
    void update() override {};

    const char *displayName() const override { return "Websocket"; }
};

namespace modes {
WebsocketMode websocketMode;
}
}
