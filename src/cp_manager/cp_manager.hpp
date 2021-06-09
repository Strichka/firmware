#pragma once

#include <SPIFFS.h>
#include "state_manager/state_manager.hpp"

class CPManager {
    public:
        CPManager();
    private:
        StateManager& stateManager;
        fs::SPIFFSFS& spiffs;
};