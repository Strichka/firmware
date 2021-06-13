#include "modes.hpp"

void debug(CRGB* leds, Led config) {
    uint8_t width = config.width / 256;
    uint8_t speed = config.speed / 256;
    uint64_t brightness = config.brightness;
    for (uint16_t i = 0; i < config.ledCount; i++) {
        leds[i].setRGB(width, speed, brightness);
    }
}

mode_function_t modes[] = {debug};
uint16_t modeCount = 1;