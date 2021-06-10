#include "nvs_manager.hpp"
#include <ArduinoNvs.h>

#define POLICY_ACCEPTED "p_a"
#define POLICY_SET "p_s"

#define LED_MODE_INDEX "l_mi"
#define LED_BRIGHTNESS "l_b"
#define LED_SPEED "l_s"
#define LED_WIDTH "l_w"
#define LED_LED_COUNT "l_lc"

#define NETWORK_AP_SSID "n_apssid"
#define NETWORK_AP_PASSWORD "n_appass"
#define NETWORK_STA_SSID "n_stassid"
#define NETWORK_STA_PASSWORD "n_stapass"

State NVSManager::readState() {
    State state;
    
    state.policy.accepted = NVS.getInt(POLICY_ACCEPTED);
    state.policy.set = NVS.getInt(POLICY_SET);

    state.ledConfig.modeIndex = NVS.getInt(LED_MODE_INDEX);
    state.ledConfig.brightness = NVS.getInt(LED_BRIGHTNESS);
    state.ledConfig.speed = NVS.getInt(LED_SPEED);
    state.ledConfig.width = NVS.getInt(LED_WIDTH);
    state.ledConfig.ledCount = NVS.getInt(LED_LED_COUNT);

    state.networkConfig.apSSID = NVS.getString(NETWORK_AP_SSID);
    state.networkConfig.apPassword = NVS.getString(NETWORK_AP_PASSWORD);
    state.networkConfig.staSSID = NVS.getString(NETWORK_STA_SSID);
    state.networkConfig.staPassword = NVS.getString(NETWORK_STA_PASSWORD);

    currentState = state;

    return state;
}

void NVSManager::writeState(State state) {
    if (currentState.policy.accepted != state.policy.accepted) {
        NVS.setInt(POLICY_ACCEPTED, state.policy.accepted);
    }
    if (currentState.policy.set != state.policy.set) {
        NVS.setInt(POLICY_SET, state.policy.set);
    }
    if (currentState.ledConfig.modeIndex != state.ledConfig.modeIndex) {
        NVS.setInt(LED_MODE_INDEX, state.policy.accepted);
    }
    if (currentState.ledConfig.brightness != state.ledConfig.brightness) {
        NVS.setInt(LED_BRIGHTNESS, state.ledConfig.brightness);
    }
    if (currentState.ledConfig.speed != state.ledConfig.speed) {
        NVS.setInt(LED_SPEED, state.ledConfig.speed);
    }
    if (currentState.ledConfig.width != state.ledConfig.width) {
        NVS.setInt(LED_WIDTH, state.policy.accepted);
    }
    if (currentState.ledConfig.ledCount != state.ledConfig.ledCount) {
        NVS.setInt(LED_LED_COUNT, state.policy.accepted);
    }
    if (currentState.networkConfig.apSSID != state.networkConfig.apSSID) {
        NVS.setString(NETWORK_AP_SSID, state.networkConfig.apSSID.toArduinoString());
    }
    if (currentState.networkConfig.apPassword != state.networkConfig.apPassword) {
        NVS.setString(NETWORK_AP_PASSWORD, state.networkConfig.apPassword.toArduinoString());
    }
    if (currentState.networkConfig.staSSID != state.networkConfig.staSSID) {
        NVS.setString(NETWORK_STA_SSID, state.networkConfig.apPassword.toArduinoString());
    }
    if (currentState.networkConfig.staPassword != state.networkConfig.staPassword) {
        NVS.setString(NETWORK_STA_PASSWORD, state.networkConfig.apPassword.toArduinoString());
    }

    currentState = state;
}

NVSManager::NVSManager() {
    NVS.begin();
    readState();
}