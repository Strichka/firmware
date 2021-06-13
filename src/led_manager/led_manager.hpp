#pragma once

#include <FastLED.h>
#include "state_manager/state_manager.hpp"

class LEDManager {
    public:
        LEDManager();
        void tick();
    private:
        StateManager& stateManager;
        CRGB* leds;
};