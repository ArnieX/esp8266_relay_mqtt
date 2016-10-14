# ESP8266 (NodeMCU) relay control

## Dependencies
- Some MQTT server (If you have Raspberry Pi use Mosquitto)
- Optional is [Homebridge](https://github.com/nfarina/homebridge) with [MQTT Plugin](https://github.com/cflurin/homebridge-mqtt) to control the relay from iDevices
- Optional that will make your life easier with IoT is Node-RED, plus you can get decent dashboard with Node-RED Dashboard plugin
- [PlatformIO](https://github.com/platformio/platformio) best Arduino IDE available, hacked from ATOM text editor

- [WiFi Manager](https://github.com/tzapu/WiFiManager)
- [PubSubClient (MQTT)](https://github.com/knolleary/pubsubclient)
- ESP8266 WiFi library

Install using PlatformIO Library Manager

```
pio lib -g install WiFiManager
pio lib -g install PubSubClient
pio lib -g install ESP8266wifi
```

## Getting started

Update main.ino with your custom preferences

[11] Set desired configuration AP name (This is used when ESP8266 isn't connected to your WiFi router to allow setup)
[12] Set password for configuration AP, so that noone else can access it in case your router is OFF
[13] Set your MQTT IP address
[14] Set your MQTT PORT

[17-21] Change MQTT topics (THIS IS OPTIONAL and I do not recommend to change it for first test of function)

[32] Set your OTA password, this will be used for secured OTA update using PlatformIO, change this respectively in platformio.ini too

[97 and 109] Uncomment and set your DATA pin which is connected to your relay

[129] Uncomment and set your DATA pin which is connected to your relay
[130] OPTIONAL: If you want your relay to turn on by default on boot, uncomment this line.

Update platformio.ini with your custom preferences (Do not change unless you want to turn OTA ON)

[14 and 15] To enable OTA for next updates uncomment these lines and change values to reflect your enviroment

To turn OTA OFF any time, just comment these lines again with ;

## Result

**Click the image to play video on YouTube:**

[![Hey Siri! Hey ESP8266!](http://img.youtube.com/vi/LSd6auz77bI/0.jpg)](https://www.youtube.com/watch?v=LSd6auz77bI)
