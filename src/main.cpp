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
}

Firmware* firmware;

void setup() {
    init_log(SERIAL_BAUDRATE);
    dependencyManager.getStateManager().state.network.staSSID = "Bigdans_2.4GHz";
    dependencyManager.getStateManager().state.network.staPassword = "07060515";
    firmware = new Firmware();
}

void loop() {
    firmware->tick();
}