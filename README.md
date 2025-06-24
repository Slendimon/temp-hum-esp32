# temp-hum-esp32

A project to monitor temperature and humidity using an ESP32 and a DHT22 sensor. Data is displayed on a web page accessible from your local WiFi network.

## Features

- Reads temperature and humidity from a DHT22 sensor.
- Displays data on a responsive web page.
- Shows current date and time using NTP.
- Simple and modern interface.

## Requirements

- ESP32
- DHT22 sensor
- Arduino IDE or PlatformIO
- Libraries: `DHT sensor library`, `WiFi`, `WebServer`

## Installation

1. Clone this repository.
2. Install the required libraries in your IDE.
3. Set your WiFi credentials in `main.cpp`:
   ```cpp
   const char* ssid     = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";
   ```
4. Connect the DHT22 sensor to GPIO 14 on the ESP32.
5. Upload the code to your ESP32.

## Usage

- After uploading, open the serial monitor to see the assigned IP address.
- Access that IP from a browser on the same WiFi network.
- View temperature, humidity, heat index, and current time.

## Credits

- Based on examples from the DHT library and ESP32 documentation.
