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

std::queue<std::map<uint16_t*, UInt16Interpolator*>::iterator> deleteQueue;

void StateManager::interpolateUInt16(uint16_t* variable, uint16_t desiredValue, uint64_t duration) {
    if (uInt16Interpolators.count(variable) > 0) {
        if (uInt16Interpolators[variable]->getDesiredValue() == desiredValue) {
            return;
        }
        deleteQueue.push(uInt16Interpolators.find(variable));
    } else {
        if (*variable == desiredValue) {
            return;
        }
    }

    uInt16Interpolators[variable] = new UInt16Interpolator(variable, desiredValue, duration, [this](UInt16Interpolator*) { storeState(); });
}

void StateManager::tick() {
    while (!deleteQueue.empty()) {
        uInt16Interpolators.erase(deleteQueue.front()->first);
        delete deleteQueue.front()->second;
        deleteQueue.pop();
    }

    for (std::map<uint16_t*, UInt16Interpolator*>::iterator it = uInt16Interpolators.begin(); it != uInt16Interpolators.end(); it++) {
        if (it->second->stopped) {
            deleteQueue.push(it);
        } else {
            it->second->tick();
        }
    }
}