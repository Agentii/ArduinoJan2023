/*
 * January 2023
 * DTU course: 34338 Telecommunication programming projects with Arduino
 * Author(s): All group members
 */

// Include the needed libraries 
#include <ESP32Servo.h> 
#include <WiFi.h>
#include <ThingSpeak.h>

// GPIO PIN decleration
const int redPIN = 27;
const int greenPIN = 26;
const int bluePIN = 25;
const int servoPIN = 33;
const int buttonPIN = 35;
const int buzzerPIN = 32;   
const int ESP32_2 = 34;
const int ESP32_2_RFID = 39;

// Global variables
int statusCode;
const unsigned int readField = 2;   // Read from field 2
const unsigned int writeField = 1;  // Write to field 1
unsigned int tsState = 1;           // ThingSpeak State from the readField
bool exitButton; 
bool isLocked = true;               // The state of the Door. 
bool ESP32_2Access = false;         // The state of the second ESP32 module
bool ESP32_2Denied = false;         // The state of the second ESP32 module
int noConnection = 0;

Servo myservo;                      // create servo object to control a servo

WiFiClient client;                  // Create a WiFi orbeject

int i = 0;                          // used for counting for the buzzer
// this is needed as the ESP32servo.h allocates all the timers (0-3) for the servo motor. 

// Internet connection details
const char* ssid = "SSID";
const char* pass = "PASS";

unsigned long channelID = 2008516;            // The ThingSpeak ChannelID
const char* APIKey = "CP79KXZ97K0TY5MZ";      // The writeAPI key from ThingSpeak
const char* ReadAPIKey = "Z9EYVRYUO0AQ2AKK";  // The readAPI key from ThingSpeak
const char* server = "api.thingspeak.com";

// The setup funktion
void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupPINS();
  
}

// The loop function
void loop() {
  handleThingSpeak();
  for(i = 0; i<2; i++) { // Running this code 2 times so the ThingSpeak does not stall the code so much.
    handleESP32_2();
    handleExitButton();
    handleLock();
  }
}

// Function for setting up the wifi connection
void setupWiFi() {
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int j = 0;
  while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++j);
    Serial.print(' ');
    if (j > 18) { // wait 18 seconds to connect and if not it will work without ThingSpeak
      Serial.print("Did not connect to internet");
      noConnection = 1;
      break;
    }    
  }
  Serial.println();

  // Enable the ThingSpeak client and start the connection.
  ThingSpeak.begin(client);
  client.connect(server, 80);  //connect(URL, Port)
}

void setupPINS() {
  pinMode(redPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  pinMode(buttonPIN, INPUT);
  pinMode(buzzerPIN, OUTPUT);
  pinMode(ESP32_2, INPUT);
  pinMode(ESP32_2_RFID, INPUT);

  // Setup for the servo motor
  myservo.setPeriodHertz(50);
  myservo.attach(servoPIN, 500, 2400);

  // Setup interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPIN), buttonPress_ISR, RISING); // We had troubles with "RISING" mode.
}

void handleLock() {
  if (exitButton || ESP32_2Access) { // check if the exit button is pressed or if the RFID, Bluetooth or snake granting access to the door.
    myservo.write(180);
    Serial.println("open");
    digitalWrite(greenPIN, HIGH);
    digitalWrite(redPIN, LOW);
    digitalWrite(bluePIN, LOW);
    openSound();
    isLocked = false;
  }
  else if (tsState == 0 && noConnection == 0) { // only if the other door is open and there is internet connection
    myservo.write(180);
    Serial.println("The other door is open");
    digitalWrite(greenPIN, HIGH);
    digitalWrite(redPIN, LOW);
    digitalWrite(bluePIN, LOW);
    tone(buzzerPIN, 440);
    isLocked = true;    // would makes sence to be "False", but this creates a infinate loof, replicating a open or locked door loop. 
  }
  else if (ESP32_2Denied ) { // if the NFC tag is denied or snake is lost the LED lights red
    myservo.write(0);
    Serial.println("RFID Denied");
    digitalWrite(redPIN, HIGH);
    digitalWrite(greenPIN, LOW);
    digitalWrite(bluePIN, LOW);
    deniedSound();
    isLocked = true;
  }
  else { // if nothing is trying to open the door 
    myservo.write(0);
    Serial.println("CLOSED");
    digitalWrite(redPIN, LOW);
    digitalWrite(greenPIN, LOW);
    digitalWrite(bluePIN, HIGH);
    noTone(buzzerPIN);
    isLocked = true;
  }
}

void handleESP32_2() {
  ESP32_2Access = digitalRead(ESP32_2);
  ESP32_2Denied = digitalRead(ESP32_2_RFID);
}

void handleThingSpeak() {
  int statusCode = ThingSpeak.getLastReadStatus();    // Get the status code for the connection to ThingSpeak. 200 is a successful connection
  if (statusCode == 200) {                                                // checks if thingspeak is ready and connected.
    tsState = ThingSpeak.readLongField(channelID, readField, ReadAPIKey); // read from TS
    Serial.print("tsState: ");  Serial.println(tsState);
    ThingSpeak.writeField(channelID, writeField, isLocked, APIKey);  //post everything to TS
  }
  else {
    Serial.println("Unable to read channel / No internet connection");
    tsState = 1;    // If the connection is lost in a unlocked state. The door retuns back to a locked state. 
  }
}

// Handle the emergency exit button. 
void handleExitButton() {
  exitButton = digitalRead(buttonPIN);
  Serial.print(exitButton);
}

void openSound () { // The sound for the door is open
  if (i == 1){
  tone(buzzerPIN, 622, 150);
  tone(buzzerPIN, 784, 150);
  tone(buzzerPIN, 830, 150);
  tone(buzzerPIN, 932, 300);
  tone(buzzerPIN, 784, 150);
  tone(buzzerPIN, 932, 300);
  noTone(buzzerPIN);
  }
}

void deniedSound () { // the sound for denied NFC tag or lost in snake
  if (i == 1){
  tone(buzzerPIN, 1047, 150);
  tone(buzzerPIN, 1397, 150);
  noTone(buzzerPIN);
  delay(150);
  tone(buzzerPIN, 1397, 150);
  noTone(buzzerPIN);
  tone(buzzerPIN, 1397, 150);
  noTone(buzzerPIN);
  delay(10);
  tone(buzzerPIN, 1319, 150);
  noTone(buzzerPIN);
  delay(10);
  tone(buzzerPIN, 1175, 150);
  noTone(buzzerPIN);
  delay(10);
  tone(buzzerPIN, 1047, 300);
  noTone(buzzerPIN);
  }
}

// The interrups service routine for the exit button
void buttonPress_ISR() {
  myservo.write(180);
  Serial.println("Interrupt Button");
  digitalWrite(greenPIN, HIGH);
  digitalWrite(redPIN, LOW);
  digitalWrite(bluePIN, HIGH);
}

