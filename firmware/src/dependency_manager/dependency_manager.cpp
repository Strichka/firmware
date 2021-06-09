#include "dependency_manager.hpp"
#include "utils/log.hpp"

#define INITIALIZATION_MESSAGE "Initialized %s\n"

DependencyManager dependencyManager;

fs::SPIFFSFS& DependencyManager::getSPIFFS() {
    if (spiffs == nullptr) {
        SPIFFS.begin();
        spiffs = &SPIFFS;
        info_logf(INITIALIZATION_MESSAGE, "SPIFFS");
    }
    return *spiffs;
}

NVSManager& DependencyManager::getNVSManager() {
    if (nvsManager == nullptr) {
        nvsManager = new NVSManager();
        info_logf(INITIALIZATION_MESSAGE, "NVSManager");
    }
    return *nvsManager;
}

StateManager& DependencyManager::getStateManager() {
    if (stateManager == nullptr) {
        stateManager = new StateManager();
        info_logf(INITIALIZATION_MESSAGE, "StateManager");
    }
    return *stateManager;
}

WiFiManager& DependencyManager::getWiFiManager() {
    if (wifiManager == nullptr) {
        wifiManager = new WiFiManager();
        info_logf(INITIALIZATION_MESSAGE, "WiFiManager");
    }
    return *wifiManager;
}

CPManager& DependencyManager::getCPManager() {
    if (cpManager == nullptr) {
        cpManager = new CPManager();
        info_logf(INITIALIZATION_MESSAGE, "CPManager");
    }
    return *cpManager;
}

LEDManager& DependencyManager::getLEDManager() {
    if (ledManager == nullptr) {
        ledManager = new LEDManager();
        info_logf(INITIALIZATION_MESSAGE, "LEDManager");
    }
    return *ledManager;
}