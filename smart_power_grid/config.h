#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const char* WIFI_SSID = "POCO_M2";
const char* WIFI_PASSWORD = "11001100";

// Pin definitions
const int POWER_SOURCE_PIN = 23;  // Digital output for power source simulation

// Area monitoring pins (Analog inputs)
const int AREA1_PIN = 32;
const int AREA2_PIN = 33;
const int AREA3_PIN = 34;
const int AREA4_PIN = 35;

// Switch control pins (Digital outputs)
const int SWITCH1_PIN = 25;
const int SWITCH2_PIN = 26;
const int SWITCH3_PIN = 27;

// Constants
const int POWER_THRESHOLD = 1000;  // Analog threshold for power loss detection
const int SWITCH_DELAY = 2000;     // Delay after switch state change (ms)

// Web server port
const int WEB_SERVER_PORT = 80;

#endif 