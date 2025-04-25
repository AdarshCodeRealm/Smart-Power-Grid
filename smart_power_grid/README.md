# Smart Power Grid Simulation

This project implements a simulated smart power grid system using an ESP32 microcontroller. The system monitors power status in four distinct areas and dynamically reconfigures power lines in response to power loss events.

## Hardware Requirements

- ESP32 Development Board
- 4 Analog Sensors (LDRs or Potentiometers) for power monitoring
- 3 LEDs (optional) for switch state indication
- Jumper wires
- Breadboard

## Pin Connections

### Power Source
- ESP32 Pin 23: Power source simulation (Digital Output)

### Area Monitoring
- ESP32 Pin 32: Area 1 power monitoring (Analog Input)
- ESP32 Pin 33: Area 2 power monitoring (Analog Input)
- ESP32 Pin 34: Area 3 power monitoring (Analog Input)
- ESP32 Pin 35: Area 4 power monitoring (Analog Input)

### Switch Control
- ESP32 Pin 25: Switch S1 control (Digital Output)
- ESP32 Pin 26: Switch S2 control (Digital Output)
- ESP32 Pin 27: Switch S3 control (Digital Output)

## Setup Instructions

1. Install the ESP32 board support in Arduino IDE:
   - Open Arduino IDE
   - Go to File > Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools > Board > Boards Manager
   - Search for "esp32" and install the package

2. Install required libraries:
   - WiFi.h (included with ESP32 board support)
   - WebServer.h (included with ESP32 board support)

3. Configure WiFi:
   - Open `config.h`
   - Update `WIFI_SSID` and `WIFI_PASSWORD` with your network credentials

4. Upload the code:
   - Select your ESP32 board from Tools > Board
   - Select the correct port from Tools > Port
   - Click Upload

## Usage

1. After uploading, open the Serial Monitor (115200 baud) to see the ESP32's IP address
2. Open a web browser and navigate to the ESP32's IP address
3. The web interface will display:
   - Current system status
   - Power levels for each area
   - Switch states
   - A block diagram of the power grid

## System Behavior

- Initial State:
  - Switch S1: ON
  - Switch S2: OFF
  - Switch S3: ON

- Area 2 Power Loss:
  - S1 turns OFF
  - S2 turns ON
  - S3 turns ON
  - 2-second delay before next change

- Area 3 Power Loss:
  - S3 turns OFF
  - S1 turns ON
  - S2 state remains unchanged
  - 2-second delay before next change

## Troubleshooting

1. If the ESP32 fails to connect to WiFi:
   - Check your WiFi credentials in `config.h`
   - Ensure your WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)

2. If the web interface is not accessible:
   - Verify the ESP32's IP address in the Serial Monitor
   - Ensure your device is on the same network as the ESP32

3. If power loss detection is not working:
   - Check the analog sensor connections
   - Adjust the `POWER_THRESHOLD` value in `config.h` if needed 