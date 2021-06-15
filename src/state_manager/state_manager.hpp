#pragma once

#include <map>
#include "nvs_manager/nvs_manager.hpp"
#include "state.hpp"

class StateManager {
    public:
        State state;

        StateManager();
        void storeState();
        void tick();
    private:
        NVSManager& nvsManager;
};