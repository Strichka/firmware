#include "network.hpp"
#include "config.hpp"
#include "utils/log.hpp"

#define MAC_SIZE 6
#define MAC_HEX_COLON_LENGTH 17

string generateAPSSID() {
    uint8_t mac[MAC_SIZE];
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);
    char* uid = new char[MAC_SIZE];
    for (uint8_t i = 0; i < 6; i++) {
        uid[i] = SSID_ALPHABET[mac[i] % SSID_ALPHABET_LENGTH];
    }
    char* ssid = new char[DEFAULT_SSID_LENGTH];
    snprintf(ssid, DEFAULT_SSID_LENGTH, DEFAULT_SSID_FORMAT, uid);
    return ssid;
}

string getMAC(esp_mac_type_t macType) {
    uint8_t mac[MAC_SIZE];
    esp_read_mac(mac, macType);
    char* stringMac = new char[MAC_HEX_COLON_LENGTH + 1];
    sprintf(stringMac, MACSTR, MAC2STR(mac));
    return stringMac;
}