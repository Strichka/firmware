#include "wifi_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"
#include "utils/log.hpp"

WiFiManager::WiFiManager() : stateManager(dependencyManager.getStateManager()) {
    string apSSID = stateManager.state.networkConfig.apSSID, apPassword = stateManager.state.networkConfig.apPassword;

    info_logf("AP SSID:\t%s\nAP password:\t%s\n", apSSID.c_str(), apPassword.c_str());

    WiFi.disconnect();
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(apSSID.c_str(), apPassword.c_str());

    info_logf("AP IP:\t\t%s\n", WiFi.softAPIP().toString().c_str());

    stateManager.state.info.apMode = true;

    string staSSID = stateManager.state.networkConfig.staSSID, staPassword = stateManager.state.networkConfig.staPassword;

    if (staSSID.length() > 0) {
        info_logf("STA SSID:\t%s\nSTA password:\t%s\n", staSSID.c_str(), staPassword.c_str());

        WiFi.begin(staSSID.c_str(), staPassword.c_str());
        
        info_log("Connecting");

        uint16_t timeout = WIFI_CONNECTION_TIMEOUT / 100;
        while (WiFi.status() != WL_CONNECTED && timeout > 0) {
            info_log(".");
            delay(100);
            timeout--;
        }

        if (WiFi.status() == WL_CONNECTED) {
            info_logln("OK");

            string staIP = WiFi.localIP().toString();
            
            stateManager.state.info.staMode = true;
            stateManager.state.info.staIP = staIP;

            info_logf("STA IP:\t\t%s\n", staIP.c_str());
        } else {
            info_logln("FAILED");
        }
    }
}