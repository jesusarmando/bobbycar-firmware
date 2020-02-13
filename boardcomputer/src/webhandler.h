#pragma once

#include <ESPAsyncWebServer.h>

namespace {
class WebHandler : public AsyncWebHandler
{
public:
    using AsyncWebHandler::AsyncWebHandler;

    bool canHandle(AsyncWebServerRequest *request) override;

    void handleRequest(AsyncWebServerRequest *request) override;
};
}
