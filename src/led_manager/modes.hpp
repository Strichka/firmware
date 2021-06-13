#pragma once

#include <functional>
#include <FastLED.h>
#include "state_manager/state.hpp"

typedef std::function<void(CRGB*, Led)> mode_function_t;

extern mode_function_t modes[];
extern uint16_t modeCount;