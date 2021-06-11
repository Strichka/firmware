#pragma once

#include <cstdint>

class UInt16Interpolator {
    public:
        bool started = false, stopped = false;
        UInt16Interpolator(uint16_t*, uint16_t, uint64_t, void(*)(UInt16Interpolator*) = nullptr);
        void tick();
    private:
        uint16_t* variable;
        uint16_t originalValue, desiredValue;
        uint64_t start, duration;
        void(*callback)(UInt16Interpolator*);
};