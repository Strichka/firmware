#include "modes.hpp"

#define LINEAR_MAP(value, in_min, in_max, out_min, out_max) (value * (out_max - out_min) / (in_max - in_min) + out_min)
#define EXPONENT_MAP(value, in_min, in_max, exp_min, exp_max) pow(2, LINEAR_MAP(value, in_min, in_max, exp_min, exp_max))

void debug(CRGB* leds, Led config) {
    uint8_t width = config.width / 256;
    uint8_t speed = config.speed / 256;
    uint64_t brightness = config.brightness;
    for (uint16_t i = 0; i < config.ledCount; i++) {
        leds[i].setRGB(width, speed, brightness);
    }
}

void rainbow(CRGB* leds, Led config) {
    double speed = EXPONENT_MAP(config.speed, 0.0, 65535.0, -2.0, 2.0);
    double width = EXPONENT_MAP(config.width, 0.0, 65535.0, 2.0, -2.0);
    
    uint64_t currentMillis = millis();

    for (uint16_t i = 0; i < config.ledCount; i++) {
        float x = float(i) / config.ledCount;
        leds[i].setHSV( (x * 255 * width + currentMillis * 0.1 * speed), 255, config.brightness);
    }
}

mode_function_t modes[] = {rainbow};
uint16_t modeCount = 1;