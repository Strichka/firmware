#include "led_manager.hpp"

#include "dependency_manager/dependency_manager.hpp"
#include "config.hpp"
#include "modes.hpp"

LEDManager::LEDManager() : stateManager(dependencyManager.getStateManager()) {
    if (stateManager.state.led.ledCount > 0) {
        leds = new CRGB[stateManager.state.led.ledCount];
        FastLED.addLeds<LED_TYPE, LED_PIN, LED_MODE>(leds, stateManager.state.led.ledCount); 
    }
}

void LEDManager::tick() {
    if (stateManager.state.led.ledCount > 0 && stateManager.state.led.modeIndex < modeCount) {
        modes[stateManager.state.led.modeIndex](leds, stateManager.state.led);
    }
    FastLED.show();
}