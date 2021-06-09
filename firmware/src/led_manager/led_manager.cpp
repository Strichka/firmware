#include "led_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {}