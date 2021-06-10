#include "state_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"
#include "utils/network.hpp"

StateManager::StateManager() : nvsManager(dependencyManager.getNVSManager()) {
    state = nvsManager.readState();

    if (state.networkConfig.apSSID.length() == 0) {
        state.networkConfig.apSSID = generateAPSSID();
    }

    if (state.networkConfig.apPassword.length() == 0) {
        state.networkConfig.apPassword = DEFAULT_AP_PASSWORD;
    }

    state.info.firmwareName = FIRMWARE_NAME;
    state.info.firmwareVersion = FIRMWARE_VERSION;

    state.info.apMAC = getMAC(ESP_MAC_WIFI_SOFTAP);
    state.info.staMAC = getMAC(ESP_MAC_WIFI_STA);

    storeState();
}

void StateManager::storeState() {
    nvsManager.writeState(state);
}