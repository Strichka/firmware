#include "state_manager.hpp"

#include <queue>
#include "dependency_manager/dependency_manager.hpp"
#include "utils/network.hpp"

StateManager::StateManager() : nvsManager(dependencyManager.getNVSManager()) {
    state = nvsManager.readState();

    if (state.network.apSSID.length() == 0) {
        state.network.apSSID = generateAPSSID();
    }

    if (state.network.apPassword.length() == 0) {
        state.network.apPassword = DEFAULT_AP_PASSWORD;
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
