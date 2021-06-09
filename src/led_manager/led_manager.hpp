#pragma once

#include "state_manager/state_manager.hpp"

class LEDManager {
    public:
        LEDManager();
    private:
        StateManager& stateManager;
};