#pragma once

#include "state_manager/state.hpp"

class NVSManager {
    public:
        NVSManager();
        State getState();
        void setState(State state);
    private:
        State currentState;
};