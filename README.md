# ESPDUINO_SDS011_MQTT

This project aims at using an ESPDUINO to collect data from a dust sensor (SDS-011) to an MQTT Broker.

Connections between ESPDUINO and SDS-011 (also works with SDS-021):

ESP RX -> SDS-0x1 pin 1 (TX)

ESP TX -> SDS-0x1 pin 2 (RX)

ESP GND -> SDS-0x1 pin 3 (GND)

ESP 5V -> SDS-0x1 pin 5 (5V)
