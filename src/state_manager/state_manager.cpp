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

void StateManager::interpolateUInt16(uint16_t* variable, uint16_t desiredValue, uint64_t duration) {
    if (uInt16Interpolators.count(variable)) {
        UInt16Interpolator* interpolator = uInt16Interpolators[variable];
        delete interpolator;
    }
    uInt16Interpolators[variable] = new UInt16Interpolator(variable, desiredValue, duration, [this](UInt16Interpolator*) { storeState(); });
}

void StateManager::tick() {
    for (std::map<uint16_t*, UInt16Interpolator*>::iterator it = uInt16Interpolators.begin(); it != uInt16Interpolators.end(); it++) {
        if (!it->second->stopped) {
            it->second->tick();
        }
    }
}