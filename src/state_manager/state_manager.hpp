#pragma once

#include <map>
#include "nvs_manager/nvs_manager.hpp"
#include "interpolator/interpolator.hpp"
#include "state.hpp"

class StateManager {
    public:
        State state;

        StateManager();
        void storeState();
        void interpolateUInt16(uint16_t* _variable, uint16_t _desiredValue, uint64_t _duration);
        void tick();
    private:
        NVSManager& nvsManager;
        std::map<uint16_t*, UInt16Interpolator*> uInt16Interpolators;
};