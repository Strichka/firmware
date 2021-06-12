#include "nvs_manager.hpp"
#include <ArduinoNvs.h>
#include "utils/log.hpp"

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

    state.led.modeIndex = NVS.getInt(LED_MODE_INDEX);
    state.led.brightness = NVS.getInt(LED_BRIGHTNESS);
    state.led.speed = NVS.getInt(LED_SPEED);
    state.led.width = NVS.getInt(LED_WIDTH);
    state.led.ledCount = NVS.getInt(LED_LED_COUNT);

    state.network.apSSID = NVS.getString(NETWORK_AP_SSID);
    state.network.apPassword = NVS.getString(NETWORK_AP_PASSWORD);
    state.network.staSSID = NVS.getString(NETWORK_STA_SSID);
    state.network.staPassword = NVS.getString(NETWORK_STA_PASSWORD);

    currentState = state;

    info_logln("State read");

    return state;
}

void NVSManager::writeState(State state) {
    if (currentState.policy.accepted != state.policy.accepted) {
        NVS.setInt(POLICY_ACCEPTED, state.policy.accepted);
    }
    if (currentState.policy.set != state.policy.set) {
        NVS.setInt(POLICY_SET, state.policy.set);
    }
    if (currentState.led.modeIndex != state.led.modeIndex) {
        NVS.setInt(LED_MODE_INDEX, state.policy.accepted);
    }
    if (currentState.led.brightness != state.led.brightness) {
        NVS.setInt(LED_BRIGHTNESS, state.led.brightness);
    }
    if (currentState.led.speed != state.led.speed) {
        NVS.setInt(LED_SPEED, state.led.speed);
    }
    if (currentState.led.width != state.led.width) {
        NVS.setInt(LED_WIDTH, state.policy.accepted);
    }
    if (currentState.led.ledCount != state.led.ledCount) {
        NVS.setInt(LED_LED_COUNT, state.policy.accepted);
    }
    if (currentState.network.apSSID != state.network.apSSID) {
        NVS.setString(NETWORK_AP_SSID, state.network.apSSID.toArduinoString());
    }
    if (currentState.network.apPassword != state.network.apPassword) {
        NVS.setString(NETWORK_AP_PASSWORD, state.network.apPassword.toArduinoString());
    }
    if (currentState.network.staSSID != state.network.staSSID) {
        NVS.setString(NETWORK_STA_SSID, state.network.apPassword.toArduinoString());
    }
    if (currentState.network.staPassword != state.network.staPassword) {
        NVS.setString(NETWORK_STA_PASSWORD, state.network.apPassword.toArduinoString());
    }

    currentState = state;

    info_logln("State written");
}

NVSManager::NVSManager() {
    NVS.begin();
    readState();
}