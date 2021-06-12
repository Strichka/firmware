#pragma once

#include <Arduino.h>
#include "string"

struct string : std::string {
    String toArduinoString();
    string(String);
    string(const char*);
    string(std::string);
    string() : std::string() {}
};
