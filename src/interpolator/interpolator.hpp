#pragma once

#include <cstdint>
#include <functional>

class UInt16Interpolator {
    public:
        bool started = false, stopped = false;
        UInt16Interpolator(uint16_t*, uint16_t, uint64_t, std::function<void(UInt16Interpolator*)> = nullptr);
        void tick();
        uint16_t getDesiredValue();
    private:
        uint16_t* variable;
        uint16_t originalValue, desiredValue;
        uint64_t start, duration;
        std::function<void(UInt16Interpolator*)> callback;
};