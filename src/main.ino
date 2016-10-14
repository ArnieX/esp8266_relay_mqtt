#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// Constants
const char* autoconf_ssid = "ESP8266_DEVICENAME"; //AP name for WiFi setup AP which your ESP will open when not able to connect to other WiFi
const char* autoconf_pwd  = "CONFIG_WIFI_PWD"; // AP password so noone else can connect to the ESP in case your router fails
const char* mqtt_server   = "XX.XX.XX.XX"; //MQTT Server IP, your home MQTT server eg Mosquitto on RPi, or some public MQTT
const int mqtt_port       = 1883; //MQTT Server PORT, default is 1883 but can be anything.

// MQTT Constants
const char* mqtt_devicestatus_set_topic    = "home/room/device_name/devicestatus"; // Change device name, but you can completely change the topics to suit your needs
const char* mqtt_pingallresponse_set_topic = "home/pingallresponse";
const char* mqtt_relayone_set_topic        = "home/room/relayone/status";
const char* mqtt_relayone_get_topic        = "home/room/relayone";
const char* mqtt_pingall_get_topic         = "home/pingall";

// Global
byte relayone_state;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_ota() {

  // Set OTA Password, and change it in platformio.ini
  ArduinoOTA.setPassword("ESP8266_PASSWORD");
  ArduinoOTA.onStart([]() {});
  ArduinoOTA.onEnd([]() {});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});
  ArduinoOTA.onError([](ota_error_t error) {
    if (error == OTA_AUTH_ERROR);          // Auth failed
    else if (error == OTA_BEGIN_ERROR);    // Begin failed
    else if (error == OTA_CONNECT_ERROR);  // Connect failed
    else if (error == OTA_RECEIVE_ERROR);  // Receive failed
    else if (error == OTA_END_ERROR);      // End failed
  });
  ArduinoOTA.begin();

}

void reconnect() {

  // MQTT reconnection function

  // Loop until we're reconnected
  while (!client.connected()) {

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {

      // Once connected, publish an announcement...
      client.publish(mqtt_devicestatus_set_topic, "connected");
      // ... and resubscribe
      client.subscribe(mqtt_relayone_get_topic);
      client.subscribe(mqtt_pingall_get_topic);

    } else {

      // Wait 5 seconds before retrying
      delay(5000);

    }

  }

}

void callback(char* topic, byte* payload, unsigned int length) {

    char c_payload[length];
    memcpy(c_payload, payload, length);
    c_payload[length] = '\0';

    String s_topic = String(topic);         // Topic
    String s_payload = String(c_payload);   // Message content

  // Handling incoming MQTT messages

    if ( s_topic == mqtt_relayone_get_topic ) {

      if (s_payload == "1") {

        if (relayone_state != 1) {

          // Turn relay ON, set HIGH/LOW depending on your relay

          // digitalWrite(Dx,HIGH);
          client.publish(mqtt_relayone_set_topic, "1");
          relayone_state = 1;

        }

      } else if (s_payload == "0") {

        if (relayone_state != 0) {

          // Turn relay OFF, set HIGH/LOW depending on your relay

          // digitalWrite(Dx,LOW);
          client.publish(mqtt_relayone_set_topic, "0");
          relayone_state = 0;

        }

      }

    } else if ( s_topic == mqtt_pingall_get_topic ) {

      client.publish(mqtt_pingallresponse_set_topic, "{\"device_name\":\"connected\"}");

    }


}

void setup() {

  //Relay setup
  //pinMode(Dx,OUTPUT);
  //digitalWrite(Dx,HIGH); // Turn ON by default ca. 0,5s after power-up

  pinMode(BUILTIN_LED, OUTPUT);     //Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect(autoconf_ssid,autoconf_password);
  setup_ota();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  digitalWrite(BUILTIN_LED, HIGH);  //Turn off LED as default, also signal that setup is over

}

void loop() {

  if (!client.connected()) {
      reconnect();
    }
    client.loop();
    ArduinoOTA.handle();

}