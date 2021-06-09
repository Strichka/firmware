#pragma once

#include <SPIFFS.h>
#include "nvs_manager/nvs_manager.hpp"
#include "state_manager/state_manager.hpp"
#include "wifi_manager/wifi_manager.hpp"
#include "cp_manager/cp_manager.hpp"
#include "led_manager/led_manager.hpp"

class DependencyManager {
    public:
        fs::SPIFFSFS& getSPIFFS();
        NVSManager& getNVSManager();
        StateManager& getStateManager();
        WiFiManager& getWiFiManager();
        CPManager& getCPManager();
        LEDManager& getLEDManager();
    private:
        fs::SPIFFSFS* spiffs = nullptr;
        NVSManager* nvsManager = nullptr;
        StateManager* stateManager = nullptr;
        WiFiManager* wifiManager = nullptr;
        CPManager* cpManager = nullptr;
        LEDManager* ledManager = nullptr;
};

extern DependencyManager dependencyManager;