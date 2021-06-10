#pragma once

#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include "state_manager/state_manager.hpp"
#include "config.hpp"

class CPManager {
    public:
        CPManager();
        void run();
    private:
        StateManager& stateManager;
        fs::SPIFFSFS& spiffs;
        AsyncWebServer webServer;
        void handleStatic(AsyncWebServerRequest* request);
};