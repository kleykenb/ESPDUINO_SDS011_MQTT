
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "SdsDustSensor.h"

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "PASSWORD"

#define AIO_SERVER      "MQTT-BROKER"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "BROKER_ACCOUNT"
#define AIO_KEY         "BROKER_PASSWORD"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish pm25 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/espduino/sds011/pm25");
Adafruit_MQTT_Publish pm10 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/espduino/sds011/pm10");


SdsDustSensor sds(Serial); // passing HardwareSerial& as parameter

void MQTT_connect();

void setup() {

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  sds.begin(); 
}

void loop() {
 
 
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;

  delay(15000);
  sds.wakeup();
  delay(15000);

  PmResult pm = sds.queryPm();

  pm25.publish(pm.pm25);
  pm10.publish(pm.pm10);

  WorkingStateResult state = sds.sleep();

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
