#pragma once

// LED
#define LED_TYPE WS2812B
#define LED_PIN GPIO_NUM_13
#define LED_MODE GRB

// WebServer configuration
#define CP_HTTP_PORT 80

// WiFi configuration
#define DEFAULT_SSID_FORMAT "Strichka-%s"
#define DEFAULT_SSID_LENGTH 13
#define SSID_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define SSID_ALPHABET_LENGTH 36
#define DEFAULT_AP_PASSWORD "12345678"
#define WIFI_CONNECTION_TIMEOUT 25000

// Firmware parameters
#define FIRMWARE_NAME "Strichka Firmware"
#define FIRMWARE_VERSION "0.0.0"

// Other
#define INTERPOLATION_DURATION 100
#define SERIAL_BAUDRATE 115200