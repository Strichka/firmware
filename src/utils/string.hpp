#include <Arduino.h>
#include "string"

struct string : std::string {
    String toArduinoString();
    string(String);
    string() : std::string() {}
};
