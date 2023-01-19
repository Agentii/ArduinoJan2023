#include <ESP8266WiFi.h>
#include <ThingSpeak.h>


const char* ssid = "Silas";
const char* pass = "silosilo";
WiFiClient client;
unsigned long channelID = 2003287; //your TS channal
const char * APIKey = "FALTSZN2LKQBW2N7"; //your TS API
const char* server = "api.thingspeak.com";
const int postDelay = 500; //post data every 20 seconds
int led = 4;

int X = 2;
int Y = 1;


void setup() {
Serial.begin(115200);
WiFi.begin(ssid, pass);
pinMode(led,INPUT);

}

float data; //measured data
float data2;

bool button;

void loop() {
data = WiFi.RSSI();
data2 = digitalRead(led);
ThingSpeak.begin(client);
client.connect(server, 80); //connect(URL, Port)
ThingSpeak.setField(X, data); //set data on the X graph
ThingSpeak.setField(Y, data2);
ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
client.stop();
delay(postDelay); //wait and then post again
}