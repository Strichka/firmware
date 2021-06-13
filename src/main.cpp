#include <Arduino.h>
#include "dependency_manager/dependency_manager.hpp"
#include "utils/log.hpp"

class Firmware {
    public:
        Firmware();
        void tick();
    private:
        LEDManager& ledManager;
        StateManager& stateManager;
};

Firmware::Firmware() : ledManager(dependencyManager.getLEDManager()), stateManager(dependencyManager.getStateManager()) {
    dependencyManager.getCPManager().run();
}

void Firmware::tick() {
    stateManager.tick();
    ledManager.tick();
}

Firmware* firmware;

void setup() {
    init_log(SERIAL_BAUDRATE);
    firmware = new Firmware();
}

void loop() {
    firmware->tick();
}