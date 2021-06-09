#include "wifi_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"

WiFiManager::WiFiManager() : stateManager(dependencyManager.getStateManager()) {}