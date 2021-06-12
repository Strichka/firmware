#include "string.hpp"

String string::toArduinoString() {
    return String(c_str());
}

string::string(String s) : std::string(s.c_str()) {}
string::string(const char* s) : std::string(s) {}
string::string(std::string s) : std::string(s) {}