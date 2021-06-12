#pragma once

#include "utils/string.hpp"

struct Policy {
    bool accepted, set;
};

struct Info {
    string firmwareName, firmwareVersion, apMAC, staMAC, staIP;
    bool apMode, staMode;
};

struct Led {
    uint16_t modeIndex, brightness, speed, width, ledCount;
};

struct Network {
    string apSSID, apPassword, staSSID, staPassword;
};

struct State {
    Policy policy;
    Info info;
    Led led;
    Network network;
};