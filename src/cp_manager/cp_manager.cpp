#include "cp_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"
#include "utils/log.hpp"

#define DEBUG_LOG_REQUEST debug_logf("%d %s\n", request->method(), request->url().c_str())

CPManager::CPManager() : stateManager(dependencyManager.getStateManager()), spiffs(dependencyManager.getSPIFFS()), webServer(80) {
    dependencyManager.getWiFiManager();
    
    webServer.on("/static/*", HTTP_GET, [this](AsyncWebServerRequest* request) {
        DEBUG_LOG_REQUEST;
        request->send(spiffs, request->url());
    });
}

void CPManager::run() {
    webServer.begin();
}