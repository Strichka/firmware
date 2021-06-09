#pragma once

#include "nvs_manager/nvs_manager.hpp"

class StateManager {
    public:
        StateManager();
    
    private:
        NVSManager& nvsManager;
};