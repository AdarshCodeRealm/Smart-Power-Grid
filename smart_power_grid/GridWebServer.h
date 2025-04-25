#ifndef GRIDWEBSERVER_H
#define GRIDWEBSERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include "PowerGrid.h"
#include "config.h"

class GridWebServer {
private:
    WebServer server;
    PowerGrid& powerGrid;

    String getStatusText() {
        if (powerGrid.getIsInDelay()) {
            return "System is in delay after switch change";
        }
        
        if (powerGrid.hasArea2PowerLoss()) {
            return "Area 2 Power Loss: Lines to Area 1 retracted, Area 2 bridged with Area 4";
        }
        else if (powerGrid.hasArea3PowerLoss()) {
            return "Area 3 Power Loss: Lines to Area 3 retracted, Area 1 and Area 2 connected";
        }
        else {
            return "Normal Operation: All areas receiving power";
        }
    }

    String getBlockDiagram() {
        String diagram = "<pre style='font-family: monospace;'>\n";
        diagram += "    [Area 1]     [Area 2]     [Area 3]     [Area 4]\n";
        diagram += "        |            |            |            |\n";
        diagram += "        |            |            |            |\n";
        
        // S1 connection
        diagram += "        +";
        diagram += powerGrid.getSwitch1State() ? "----" : "    ";
        diagram += "--------+            |            |\n";
        
        // S2 connection
        diagram += "                    +";
        diagram += powerGrid.getSwitch2State() ? "----" : "    ";
        diagram += "--------+            |\n";
        
        // S3 connection
        diagram += "                                +";
        diagram += powerGrid.getSwitch3State() ? "----" : "    ";
        diagram += "--------+\n";
        
        diagram += "</pre>";
        return diagram;
    }

    void handleRoot() {
        String html = "<!DOCTYPE html><html><head>";
        html += "<title>Smart Power Grid</title>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<style>";
        html += "body { font-family: Arial, sans-serif; margin: 20px; }";
        html += "h1 { color: #2c3e50; }";
        html += ".status { background-color: #f8f9fa; padding: 15px; border-radius: 5px; margin: 10px 0; }";
        html += ".values { display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; }";
        html += ".value-box { background-color: #e9ecef; padding: 10px; border-radius: 5px; }";
        html += ".switch-control { display: flex; align-items: center; gap: 10px; margin: 10px 0; }";
        html += ".switch-btn { padding: 8px 20px; border: none; border-radius: 5px; cursor: pointer; font-weight: bold; }";
        html += ".switch-btn.on { background-color: #28a745; color: white; }";
        html += ".switch-btn.off { background-color: #dc3545; color: white; }";
        html += ".switch-btn:disabled { opacity: 0.5; cursor: not-allowed; }";
        html += "</style>";
        html += "<script>";
        html += "function updateValues() {";
        html += "  fetch('/values')";
        html += "    .then(response => response.json())";
        html += "    .then(data => {";
        html += "      document.getElementById('area1').textContent = data.area1;";
        html += "      document.getElementById('area2').textContent = data.area2;";
        html += "      document.getElementById('area3').textContent = data.area3;";
        html += "      document.getElementById('area4').textContent = data.area4;";
        html += "      document.getElementById('switch1').textContent = data.switch1 ? 'ON' : 'OFF';";
        html += "      document.getElementById('switch2').textContent = data.switch2 ? 'ON' : 'OFF';";
        html += "      document.getElementById('switch3').textContent = data.switch3 ? 'ON' : 'OFF';";
        html += "      document.getElementById('status').textContent = data.status;";
        html += "      document.getElementById('diagram').innerHTML = data.diagram;";
        html += "      updateSwitchButtons();";
        html += "    });";
        html += "}";
        html += "function updateSwitchButtons() {";
        html += "  const switches = ['switch1', 'switch2', 'switch3'];";
        html += "  switches.forEach(sw => {";
        html += "    const state = document.getElementById(sw).textContent === 'ON';";
        html += "    const onBtn = document.getElementById(sw + '_on');";
        html += "    const offBtn = document.getElementById(sw + '_off');";
        html += "    onBtn.className = 'switch-btn on' + (state ? ' active' : '');";
        html += "    offBtn.className = 'switch-btn off' + (!state ? ' active' : '');";
        html += "    onBtn.disabled = state;";
        html += "    offBtn.disabled = !state;";
        html += "  });";
        html += "}";
        html += "function toggleSwitch(switchNum, state) {";
        html += "  const url = '/toggle/' + switchNum + '/' + (state ? '1' : '0');";
        html += "  fetch(url)";
        html += "    .then(response => {";
        html += "      if (response.ok) {";
        html += "        updateValues();";
        html += "      } else {";
        html += "        console.error('Failed to toggle switch');";
        html += "      }";
        html += "    })";
        html += "    .catch(error => {";
        html += "      console.error('Error:', error);";
        html += "    });";
        html += "}";
        html += "// Update immediately and then every second";
        html += "updateValues();";
        html += "setInterval(updateValues, 1000);";
        html += "</script>";
        html += "</head><body>";
        
        html += "<h1>Smart Power Grid</h1>";
        
        // Status text
        html += "<div class='status'>";
        html += "<h2>System Status</h2>";
        html += "<p id='status'>" + getStatusText() + "</p>";
        html += "</div>";
        
        // Power values
        html += "<div class='values'>";
        html += "<div class='value-box'><h3>Area 1 Power</h3><p id='area1'>" + String(powerGrid.getArea1Power()) + "</p></div>";
        html += "<div class='value-box'><h3>Area 2 Power</h3><p id='area2'>" + String(powerGrid.getArea2Power()) + "</p></div>";
        html += "<div class='value-box'><h3>Area 3 Power</h3><p id='area3'>" + String(powerGrid.getArea3Power()) + "</p></div>";
        html += "<div class='value-box'><h3>Area 4 Power</h3><p id='area4'>" + String(powerGrid.getArea4Power()) + "</p></div>";
        html += "</div>";
        
        // Switch states with manual control
        html += "<div class='status'>";
        html += "<h2>Switch States</h2>";
        html += "<div class='switch-control'>";
        html += "<p>S1: <span id='switch1'>" + String(powerGrid.getSwitch1State() ? "ON" : "OFF") + "</span></p>";
        html += "<button id='switch1_on' class='switch-btn on' onclick='toggleSwitch(1, true)'>ON</button>";
        html += "<button id='switch1_off' class='switch-btn off' onclick='toggleSwitch(1, false)'>OFF</button>";
        html += "</div>";
        html += "<div class='switch-control'>";
        html += "<p>S2: <span id='switch2'>" + String(powerGrid.getSwitch2State() ? "ON" : "OFF") + "</span></p>";
        html += "<button id='switch2_on' class='switch-btn on' onclick='toggleSwitch(2, true)'>ON</button>";
        html += "<button id='switch2_off' class='switch-btn off' onclick='toggleSwitch(2, false)'>OFF</button>";
        html += "</div>";
        html += "<div class='switch-control'>";
        html += "<p>S3: <span id='switch3'>" + String(powerGrid.getSwitch3State() ? "ON" : "OFF") + "</span></p>";
        html += "<button id='switch3_on' class='switch-btn on' onclick='toggleSwitch(3, true)'>ON</button>";
        html += "<button id='switch3_off' class='switch-btn off' onclick='toggleSwitch(3, false)'>OFF</button>";
        html += "</div>";
        html += "</div>";
        
        // Block diagram
        html += "<div class='status'>";
        html += "<h2>Power Grid Diagram</h2>";
        html += "<div id='diagram'>" + getBlockDiagram() + "</div>";
        html += "</div>";
        
        html += "</body></html>";
        server.send(200, "text/html", html);
    }

    void handleValues() {
        String json = "{";
        json += "\"area1\":" + String(powerGrid.getArea1Power()) + ",";
        json += "\"area2\":" + String(powerGrid.getArea2Power()) + ",";
        json += "\"area3\":" + String(powerGrid.getArea3Power()) + ",";
        json += "\"area4\":" + String(powerGrid.getArea4Power()) + ",";
        json += "\"switch1\":" + String(powerGrid.getSwitch1State()) + ",";
        json += "\"switch2\":" + String(powerGrid.getSwitch2State()) + ",";
        json += "\"switch3\":" + String(powerGrid.getSwitch3State()) + ",";
        json += "\"status\":\"" + getStatusText() + "\",";
        json += "\"diagram\":\"" + getBlockDiagram() + "\"";
        json += "}";
        server.send(200, "application/json", json);
    }

    void handleToggle() {
        if (server.args() != 2) {
            server.send(400, "text/plain", "Bad Request");
            return;
        }

        int switchNum = server.arg(0).toInt();
        bool state = server.arg(1).toInt() == 1;

        if (switchNum < 1 || switchNum > 3) {
            server.send(400, "text/plain", "Invalid switch number");
            return;
        }

        if (powerGrid.getIsInDelay()) {
            server.send(400, "text/plain", "System is in delay");
            return;
        }

        switch (switchNum) {
            case 1:
                powerGrid.setSwitch1State(state);
                break;
            case 2:
                powerGrid.setSwitch2State(state);
                break;
            case 3:
                powerGrid.setSwitch3State(state);
                break;
        }

        server.send(200, "text/plain", "OK");
    }

public:
    GridWebServer(PowerGrid& pg) : server(WEB_SERVER_PORT), powerGrid(pg) {}

    void begin() {
        server.on("/", [this]() { handleRoot(); });
        server.on("/values", [this]() { handleValues(); });
        server.on("/toggle/1/0", [this]() { handleToggle(); });
        server.on("/toggle/1/1", [this]() { handleToggle(); });
        server.on("/toggle/2/0", [this]() { handleToggle(); });
        server.on("/toggle/2/1", [this]() { handleToggle(); });
        server.on("/toggle/3/0", [this]() { handleToggle(); });
        server.on("/toggle/3/1", [this]() { handleToggle(); });
        server.begin();
    }

    void update() {
        server.handleClient();
    }
};

#endif 