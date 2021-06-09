#pragma once

#include "utils/string.hpp"

struct Policy {
    bool accepted, set;
};

struct Info {
    string firmwareName, firmwareVersion, apMAC, staMAC, staIP;
    bool apMode, staMode;
};

struct LedConfig {
    uint16_t modeIndex, brightness, speed, width, ledCount;
};

struct NetworkConfig {
    string apSSID, apPassword, staSSID, staPassword;
};

struct State {
    Policy policy;
    Info info;
    LedConfig ledConfig;
    NetworkConfig networkConfig;
};