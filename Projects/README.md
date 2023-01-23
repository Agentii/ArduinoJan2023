# Smart Door and Ventilation System
## Smart Home IoT project on ESP8266 and ESP32 modules

# Table of contents
1. [About](#about)<br>
2. [Setup and installation](#setup)<br>
  a.  [Assembling the circuits](#circuits)<br>
  b.  [Installing libraries](#libraries)<br>

### About <a name="about"/>
This repo contains an IoT project which was made as part of the final assignment in the course 34338 Telecommunication programming projects with Arduino at the Technical University of Denmark.<br>
The project is a prototype of a smart door lock system and ventilation system. The project is build on four ESP32 MCUs (for the door lock system) and one ESP8266 MCU (for the ventilation system). The ESP32 modules are connected to ThingSpeak and the ESP8266 hosts a local webserver.<br>
Inspiration for the webserver is taken from [Random Nerd Tutorials - ESP8266 DHT11/DHT22 Temperature and Humidity Web Server with Arduino IDE](https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/).

### Setup and installation <a name="setup"/>
To set up this project for recreation purposes, you will need the following components:
<ul>
<li> 4 ESP32 MCUs </li>
<li> 1 ESP8266 MCU </li>
<li> 2 NFC/RFID sensor + tag/card </li>
<li> 1 DHT11 humidity sensor </li>
<li> 1 dc motor </li>
<li> 2 8x8 MAX7219 dot matrix </li>
<li> 2 joysticks </li>
<li> 2 RGB LED's </li>
<li> 2 buzzers </li>
<li> 1 relay </li>
<li> 3 power supply modules </li>
<li> 2 servo motors </li>
<li> 2 buttons </li>
<li> jumper wires </li>
</ul>

#### Assembling the circuits <a name="circuits"/>
The Fritzing diagrams for the builds are only available in the report through DTU Learn.

#### Installing libraries <a name="libraries"/>
The libraries necessary for running the scripts are the following. Most of them can be installed through the Arduino IDE.
<ul>
<li> ThingSpeak by MathWorks </li>
<li> MD_Parola by MajicDesigns </li>
<li> MD_MAX72XX by MajicDesigns </li>
<li> DHT sensor library by Adafruit </li>
<li> Adafruit unified Sensor by Adafruit </li>
<li> Adafruit ESP8266 by Adafruit </li>
<li> WiFiNINA by Arduino </li>
<li> Esplora by Arduino </li>
<li> EduIntro by Arduino LLC </li>
<li> Arduino_LSM6DS3 by Arduino </li>
<li> ESPAsyncTCP* </li>
<li> ESPAsyncWebSErver* </li>
<li>  </li>
<li>  </li>
<li>  </li>
<li>  </li>
</ul>

\* Note:
The Async webserver libraries can be installed from their respective GitHubs.<br>
https://github.com/me-no-dev/ESPAsyncTCP<br>
https://github.com/me-no-dev/ESPAsyncWebServer
