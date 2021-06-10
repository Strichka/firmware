#pragma once

#include "state_manager/state.hpp"

class NVSManager {
    public:
        NVSManager();
        State readState();
        void writeState(State state);
    private:
        State currentState;
};