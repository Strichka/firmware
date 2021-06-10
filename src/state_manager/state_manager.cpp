#include "state_manager.hpp"
#include "dependency_manager/dependency_manager.hpp"

StateManager::StateManager() : nvsManager(dependencyManager.getNVSManager()) {
    state = nvsManager.readState();
}

void StateManager::storeState() {
    nvsManager.writeState(state);
}