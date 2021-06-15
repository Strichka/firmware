#include "cp_manager.hpp"

#include <ArduinoJson.h>
#include <AsyncJson.h>
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

    webServer.on("/v0/restart", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        request->send(STATUS_OK);

        stateManager.storeState();

        ESP.restart();
    });

    webServer.on("/v0/ping", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;
        
        request->send(STATUS_OK);
    });

    webServer.on("/v0/policy", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;
        
        if (stateManager.state.policy.set) {
            json["accepted"] = stateManager.state.policy.accepted;
        } else {
            json["accepted"] = nullptr;
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

    webServer.on("/v0/led", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;

        json["mode_index"] = stateManager.state.led.modeIndex;
        json["brightness"] = stateManager.state.led.brightness;
        json["speed"] = stateManager.state.led.speed;
        json["width"] = stateManager.state.led.width;
        json["led_count"] = stateManager.state.led.ledCount;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());
    });

    webServer.on("/v0/network", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;

        StaticJsonDocument<JSON_SIZE> json;

        json["ap_ssid"] = (std::string) stateManager.state.network.apSSID;
        json["ap_password"] = (std::string) stateManager.state.network.apPassword;
        json["sta_ssid"] = (std::string) stateManager.state.network.staSSID;
        json["sta_password"] = (std::string) stateManager.state.network.staPassword;

        string jsonString;

        serializeJson(json, (std::string&) jsonString);

        request->send(STATUS_OK, CONTENT_TYPE_JSON, jsonString.c_str());
    });

    AsyncCallbackJsonWebHandler* postPolicy = new AsyncCallbackJsonWebHandler("/v0/policy", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        DEBUG_LOG_REQUEST;

        if (json["accepted"] == nullptr) {
            stateManager.state.policy.set = false;
        } else {
            stateManager.state.policy.set = true;
            stateManager.state.policy.accepted = json["accepted"];
        }

        stateManager.storeState();

        request->send(STATUS_OK);
    });

    AsyncCallbackJsonWebHandler* postLed = new AsyncCallbackJsonWebHandler("/v0/led", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        DEBUG_LOG_REQUEST;

        stateManager.state.led.modeIndex = json["mode_index"];
        stateManager.state.led.ledCount = json["led_count"];
        stateManager.state.led.brightness = json["brightness"];
        stateManager.state.led.speed = json["speed"];
        stateManager.state.led.width = json["width"];

        stateManager.storeState();

        request->send(STATUS_OK);
    });

    AsyncCallbackJsonWebHandler* postNetwork = new AsyncCallbackJsonWebHandler("/v0/network", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        DEBUG_LOG_REQUEST;

        std::string apSSID = json["ap_ssid"];
        std::string apPassword = json["ap_password"];
        std::string staSSID = json["sta_ssid"];
        std::string staPassword = json["sta_password"];

        stateManager.state.network.apSSID = apSSID;
        stateManager.state.network.apPassword = apPassword;
        stateManager.state.network.staSSID = staSSID;
        stateManager.state.network.staPassword = staPassword;

        stateManager.storeState();

        request->send(STATUS_OK);
    });

    webServer.addHandler(postPolicy);
    webServer.addHandler(postLed);
    webServer.addHandler(postNetwork);
}

void CPManager::run() {
    info_logln("Running control panel webserver");
    webServer.begin();
}