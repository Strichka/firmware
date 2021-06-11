#include "cp_manager.hpp"

#include <ArduinoJson.h>
#include "dependency_manager/dependency_manager.hpp"
#include "utils/string.hpp"
#include "utils/log.hpp"

#define DEBUG_LOG_REQUEST debug_logf("%d %s\n", request->method(), request->url().c_str())

#define STATUS_OK 200
#define CONTENT_TYPE_JSON "application/json"
#define CONTENT_TYPE_PLAINTEXT "text/plain"
#define JSON_SIZE 256

CPManager::CPManager() : stateManager(dependencyManager.getStateManager()), spiffs(dependencyManager.getSPIFFS()), webServer(80) {
    dependencyManager.getWiFiManager();
    
    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;
        
        request->send(spiffs, request->url());
    });

    webServer.on("/v0/ping", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;
        
        request->send(STATUS_OK);
    });

    webServer.on("/v0/policy", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;
        
        if (stateManager.state.policy.set) {
            json["policy"] = stateManager.state.policy.accepted;
        } else {
            json["policy"] = nullptr;
        }

        string jsonString;
        
        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());        
    });

    webServer.on("/v0/info", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;

        json["firmware_name"] = (std::string) stateManager.state.info.firmwareName;
        json["firmware_version"] = (std::string) stateManager.state.info.firmwareVersion;
        json["ap_mode"] = stateManager.state.info.apMode;
        json["sta_mode"] = stateManager.state.info.staMode;
        json["ap_mac"] = (std::string) stateManager.state.info.apMAC;
        json["sta_mac"] = (std::string) stateManager.state.info.staMAC;
        json["sta_ip"] = (std::string) stateManager.state.info.staIP;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());
    });

    webServer.on("/v0/led/config", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;

        json["mode_index"] = stateManager.state.ledConfig.modeIndex;
        json["brightness"] = stateManager.state.ledConfig.brightness;
        json["speed"] = stateManager.state.ledConfig.speed;
        json["width"] = stateManager.state.ledConfig.width;
        json["led_count"] = stateManager.state.ledConfig.ledCount;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());
    });

    webServer.on("/v0/network/config", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;

        json["ap_ssid"] = (std::string) stateManager.state.networkConfig.apSSID;
        json["ap_password"] = (std::string) stateManager.state.networkConfig.apPassword;
        json["sta_ssid"] = (std::string) stateManager.state.networkConfig.staSSID;
        json["sta_password"] = (std::string) stateManager.state.networkConfig.staPassword;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());
    });
}

void CPManager::run() {
    info_logln("Running control panel webserver");
    webServer.begin();
}