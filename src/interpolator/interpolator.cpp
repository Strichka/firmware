#include "interpolator.hpp"

#include <Arduino.h>

UInt16Interpolator::UInt16Interpolator(uint16_t* _variable, uint16_t _desiredValue, uint64_t _duration, std::function<void(UInt16Interpolator*)> _callback) {
    variable = _variable;
    originalValue = *_variable;
    desiredValue = _desiredValue;
    duration = _duration;
    callback = _callback;
}

void UInt16Interpolator::tick() {
    if (stopped) {
        return;
    }
    if (!started) {
        start = millis();
        started = true;
    }
    double t = (double) (millis() - start) / (double) duration;
    *variable = originalValue + (desiredValue - originalValue) * t;
    if (t >= 1.0) {
        stopped = true;
        if (callback != nullptr) {
            callback(this);
        }
        return;
    }
}