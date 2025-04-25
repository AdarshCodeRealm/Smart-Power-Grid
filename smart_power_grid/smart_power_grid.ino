#include <WiFi.h>
#include "config.h"
#include "PowerGrid.h"
#include "GridWebServer.h"

PowerGrid powerGrid;
GridWebServer webServer(powerGrid);

void setup() {
    Serial.begin(115200);
    
    // Initialize power grid
    powerGrid.begin();
    
    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    // Initialize web server
    webServer.begin();
}

void loop() {
    // Update power grid state
    powerGrid.update();
    
    // Check for power loss conditions
    if (powerGrid.hasArea2PowerLoss()) {
        powerGrid.handleArea2PowerLoss();
    }
    else if (powerGrid.hasArea3PowerLoss()) {
        powerGrid.handleArea3PowerLoss();
    }
    
    // Update web server
    webServer.update();
    
    // Small delay to prevent overwhelming the system
    delay(100);
} 