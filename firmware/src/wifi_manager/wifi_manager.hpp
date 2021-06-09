#pragma once

#include "state_manager/state_manager.hpp"

class WiFiManager {
    public:
        WiFiManager();
    private:
        StateManager& stateManager;
};