# ESP8266 (NodeMCU) relay control

This project was the first thing I did with NodeMCU. I hope that following this README will be as straightforward as possible. In case you have questions do not hesitate to contact me using [Issues](https://github.com/ArnieX/esp8266_relay_mqtt/issues).

## Check out my new repository with ESP8266 equipped HW - [SWIFITCH](https://github.com/ArnieX/swifitch)

If you want to be able to change LED Strip brightness too follow my other project: [LED Strip Dimming using MOSFET](https://github.com/ArnieX/esp8266_dimmer_mqtt)

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

- [11] Set desired configuration AP name (This is used when ESP8266 isn't connected to your WiFi router to allow setup)
- [12] Set password for configuration AP, so that noone else can access it in case your router is OFF
- [13] Set your MQTT IP address
- [14] Set your MQTT PORT

- [17-21] Change MQTT topics (THIS IS OPTIONAL and I do not recommend to change it for first test of function)

- [33] Set your OTA password, this will be used for secured OTA update using PlatformIO, change this respectively in platformio.ini too

- [90 and 102] Uncomment and set your DATA pin which is connected to your relay

- [123] Uncomment and set your DATA pin which is connected to your relay
- [124] OPTIONAL: If you want your relay to turn on by default on boot, uncomment this line.

Update platformio.ini with your custom preferences (Do not change unless you want to turn OTA ON)

- [14 and 15] To enable OTA for next updates uncomment these lines and change values to reflect your enviroment

To turn OTA OFF any time, just comment these lines again with ;

## Usage

Send command through your MQTT server as such:

|TOPIC|DESCRIPTION|
|---|---|
|home/room/relayone|Send 1/0 to turn ON/OFF|
|home/pingall|Send whatever and you get response at topic home/pingallresponse|

Receive back from your device:

|TOPIC|DESCRIPTION|
|---|---|
|home/room/device_name/devicestatus|Will contain device status eg connected|
|home/pingallresponse|This will contain status after you send pingall request and all devices should respond|
|home/room/relayone/status|This listens for status change to set correct status eg in Homebridge|

## Result

**Click the image to play video on YouTube:**

[![Hey Siri! Hey ESP8266!](http://img.youtube.com/vi/LSd6auz77bI/0.jpg)](https://www.youtube.com/watch?v=LSd6auz77bI)
