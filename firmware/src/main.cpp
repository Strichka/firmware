#include <Arduino.h>
#include "dependency_manager/dependency_manager.hpp"
#include "utils/log.hpp"

class Firmware {
    public:
        Firmware();
        void tick();
    private:
        LEDManager& ledManager;
};

Firmware::Firmware() : ledManager(dependencyManager.getLEDManager()) {
    dependencyManager.getCPManager();
}

void Firmware::tick() {}

Firmware* firmware;

void setup() {
    init_log(115200);
    firmware = new Firmware();
}

void loop() {
    firmware->tick();
}