#pragma once

#include "nvs_manager/nvs_manager.hpp"
#include "state.hpp"

class StateManager {
    public:
        State state;

        StateManager();
        void storeState();
    private:
        NVSManager& nvsManager;
};