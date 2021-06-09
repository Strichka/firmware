#include "cp_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"

CPManager::CPManager() : stateManager(dependencyManager.getStateManager()), spiffs(dependencyManager.getSPIFFS()) {
    dependencyManager.getWiFiManager();
}