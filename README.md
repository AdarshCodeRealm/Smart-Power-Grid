# Smart Power Grid Monitor

A comprehensive power grid monitoring system using ESP32, featuring real-time voltage monitoring, switch control, and data logging to MongoDB.

![Project Overview](assets/project-overview.png)

## Features

- Real-time voltage monitoring using 4 analog pins
- 3 switch control outputs with automatic voltage-based control
- Web interface with live updates
- MongoDB integration for data logging
- Automatic data synchronization
- Responsive web dashboard
- Visual feedback for changes
- Server status monitoring

## Hardware Requirements

- ESP32 Development Board
- 4 Analog Sensors (voltage sensors)
- 3 Relays/Switches
- Jumper Wires
- Power Supply (3.3V)

## Pin Configuration

### Analog Inputs (Right Side Pins)
- GPIO32 (ADC1_CH4)
- GPIO33 (ADC1_CH5)
- GPIO34 (ADC1_CH6)
- GPIO35 (ADC1_CH7)

### Switch Outputs (Right Side Pins)
- GPIO25 (Switch 1)
- GPIO26 (Switch 2)
- GPIO27 (Switch 3)

### Constant High Output
- GPIO23 (Always HIGH)

## Software Requirements

### ESP32 Requirements
- Arduino IDE
- ESP32 Board Support Package
- Required Libraries:
  - WiFi.h
  - WebServer.h
  - HTTPClient.h

### Backend Requirements
- Node.js
- MongoDB
- Required npm packages:
  - express
  - mongoose
  - cors
  - dotenv
  - body-parser
  - express-validator
  - moment

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/smart-power-grid.git
cd smart-power-grid
```

2. Install backend dependencies:
```bash
cd backend
npm install
```

3. Configure environment variables:
   - Copy `.env.example` to `.env`
   - Update MongoDB connection string
   - Set your WiFi credentials

4. Upload ESP32 code:
   - Open `power_grid_monitor.ino` in Arduino IDE
   - Update WiFi credentials in `config.h`
   - Upload to ESP32

## Usage

1. Start the backend server:
```bash
cd backend
npm start
```

2. Access the web interface:
   - Open browser and navigate to ESP32's IP address
   - Default URL: `http://<esp32-ip-address>/`

3. Monitor data:
   - View real-time voltage readings
   - Control switches manually
   - Monitor server connection status
   - View historical data through MongoDB

## API Endpoints

### ESP32 Web Server
- `GET /` - Web interface
- `GET /data` - Get current sensor data
- `POST /switch` - Control switches

### Backend Server
- `POST /api/sensor-data` - Save sensor data
- `GET /api/sensor-data/latest` - Get latest readings
- `GET /api/sensor-data/history` - Get historical data
- `GET /api/sensor-data/stats` - Get statistical data

## Data Structure

### Sensor Data Schema
```javascript
{
    timestamp: Date,
    deviceId: String,
    analogReadings: [{
        pinNumber: Number,
        rawValue: Number,
        voltage: Number
    }],
    switchStates: [{
        pinNumber: Number,
        state: Boolean
    }]
}
```

## Features in Detail

### Real-time Monitoring
- Updates every second on web interface
- Server synchronization every 5 seconds
- Visual feedback for value changes
- Automatic switch control based on voltage thresholds

### Web Interface
- Responsive design
- Live updates without page refresh
- Switch control buttons
- Server status indicator
- Historical data viewing

### Data Logging
- MongoDB integration
- Automatic data synchronization
- Historical data storage
- Statistical analysis

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- ESP32 Arduino Core
- Express.js
- MongoDB
- Bootstrap
- Chart.js

## Contact

Your Name - your.email@example.com
Project Link: [https://github.com/yourusername/smart-power-grid](https://github.com/yourusername/smart-power-grid)
