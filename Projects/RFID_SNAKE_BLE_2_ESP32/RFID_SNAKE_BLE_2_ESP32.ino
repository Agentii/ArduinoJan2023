#include <SPI.h>
#include <MFRC522.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Define the reset and sda pin for the RFID
#define RST_PIN 2
#define SS_PIN 5

// Defining size, and output pins for the matrix. 
#define MAX_DEVICES 1 // Define the number of displays connected.
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN 14 // or SCK
#define DATA_PIN 4 // or MOSI
#define CS_PIN 15 // or SS
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

// Create display as intances for the 8x8 matrix with the different pins as listed above.
MD_MAX72XX Display = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Define the Joystick pins and the upper and lower threshold.
#define JOY_PIN_X 34
#define JOY_PIN_Y 35
#define JOY_UPPER_THRESHOLD 4050
#define JOY_LOWER_THRESHOLD 50

// these two pins are usen to send information from this ESP32 to the other ESP32 running Thingspeak.
const int accesGranted = 21;
const int accesDenied = 22;


// Defining the acces tags and readcard
byte readCard[4];
String tag1 = "31E1201D" , tag2 = "2465ABD2", tag3 = "A64834F" , tag4 = "5F63ADB4";	// This is the different tagID's that is allow to acces the door.
String tagID = "";

// Create instance for the RFID/NFC tag 
MFRC522 mfrc522(SS_PIN, RST_PIN);


// Creating instances and different values for the Bluethooth on the ESP32
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // Creating the ID for the Bluetooth module.
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Creating a class for detecing if a device is connected to the ESP32 Bluetooth module.
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void(* resetFunc) (void) = 0;




// snake from here and below
const unsigned long TICK_RATE = 200;

unsigned long startMillis = 0;
unsigned long currentMillis = 0;

unsigned int score = 0;

struct Snake {
  signed char vx;  // Velocity [LEDs per tick] in x direction (-1, 0 or 1)
  signed char vy;  // velocity [LEDs per tick] in y direction (-1, 0 or 1)
  unsigned int size;
  bool isDead;  
} snake;

typedef struct Coordinates {
 int x;
 int y;
} Coords;

typedef struct SnakePart SnakePart;
struct SnakePart {
  Coords coords;
  SnakePart *next_ptr;  // Points to next body part (from tail towards head). Head points to NULL.
};

Coords joystick, fruitCoords;
SnakePart head, body, tail, *head_ptr, *tail_ptr;

// We have the snake code from: 
//


void setup() 
{
  // Initiating the NFC tag
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522

//  starting the serial
  Serial.begin(115200);

//  Initialize the Display 8x8 mttrix.
  Display.begin();
	Display.clear();  // clears all of the LED's in the display.

//  Initialize the different pins
  pinMode(accesGranted, OUTPUT); // pin output to the other ESP32
  pinMode(accesDenied, OUTPUT); // pin output to the other ESP32
  pinMode(25, INPUT_PULLUP); //  the input from the joystick


//  initialize the Bluetoot on the ESP32 
  initBLE();
}

void loop() 
{
  // Checks for the ID to get acces the door
  handleID();  
  // Checks for the Bluetooth to open the door
  handleBLE();
  // Checks for the Snake game to get acces the door
  handleSnake();
}


void handleID(){
  while (getID()){
    if (tagID == tag1 || tagID == tag2 || tagID == tag3 || tagID == tag4) // checks if the tag is one of tags that have acces.
    {
    digitalWrite(accesGranted, HIGH);
    digitalWrite(accesDenied, LOW);
    delay(15000); 

    } else { // If the tagID is not the correct tagID the code sets the denied pin to HIGH and lets the other ESP32 know that the tag is denied.
      digitalWrite(accesGranted, LOW);
      digitalWrite(accesDenied, HIGH);
      delay(15000);
    }
    
    //Serial.println(tagID);  // uncomment this section if you want to see the tagID from the tag you scan

    } 
}




void handleBLE () {
 if(deviceConnected == true){
    //Serial.println("connected");  // uncomment this if you want it to show the status of the bluetooth connected
    digitalWrite(accesGranted, HIGH);
    delay(1000);

  } else {
   // Serial.println("disconnected");  // uncomment this if you want it to show the status of the bluetooth connected
    digitalWrite(accesGranted, LOW);   
  }
}


void handleSnake(){
  
 if (!digitalRead(25)){ // checks if the button on the joystick is pressed and start the game if it pressed. 
    initializeSnake();
    initializeJoystick();
    spawnFruit();
    while(1) {
    snakeTheGame();
    if (!digitalRead(25)||snake.isDead) { // If the button on the joystick or you die in snake you exit the game.
      score = 0;
      SPI.begin(); // the RFID/NFC tag needs to be initialized again before it will work after running snake the game. 
      mfrc522.PCD_Init(); // the RFID/NFC tag needs to be initialized again before it will work after running snake the game. 
      Display.clear();  // clearing the screen.
      digitalWrite(accesGranted, LOW);
      digitalWrite(accesDenied, HIGH); // setting the denied TRUE to let the other ESP32 know that the 
      delay(15000); // wait 15 seconds so we are sure that it is oploaded to ThingSpeak
      break; // break out of the loop
    } else if (score==8){ // if you score 8 points you win the snake game! jaaaaaa!
    digitalWrite(accesGranted, HIGH);
    digitalWrite(accesDenied, LOW);
    SPI.begin(); // the RFID/NFC tag needs to be initialized again before it will work after running snake the game.
    mfrc522.PCD_Init(); // the RFID/NFC tag needs to be initialized again before it will work after running snake the game.
    Display.clear(); // clearing the screen.
    delay(15000);// wait 15 seconds so we are sure that it is oploaded to ThingSpeak
    score = 0; // resets the score to zero so you can play again!
    break; // break out of the loop
    }
    }
    }
}



void initBLE() {

   // Create the BLE Device
  BLEDevice::init("ESP32_2");
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // We used this code for the Bluetooth:
  // https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}



//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}


void snakeTheGame() {
    //while (snake.isDead) {} 
  do {
    readJoystick();
    updateVelocity();
  } while (snake.vx == 0 && snake.vy == 0);  // Await input from joystick when snake isn't moving
  
  updateGame();
}



void initializeSnake() {
  // Set snake start position
  head.coords.x = 4;
  head.coords.y = 4;

  // Initialize pointers for the snake
  head.next_ptr = NULL;
  head_ptr = &head;
  tail_ptr = head_ptr;

  snake.size = 1;
  snake.isDead = false;
  snake.vx = 0;
  snake.vy = 0;

  updateMatrix(head.coords, HIGH); 
}

void initializeJoystick() {
  joystick.x = 2000;
  joystick.y = 2000;
}

void readJoystick() {
  joystick.x = analogRead(JOY_PIN_X);
  joystick.y = analogRead(JOY_PIN_Y);
  Serial.print(joystick.x);
  Serial.print(", ");
  Serial.println(joystick.y);
}

void updateVelocity() {
  if (joystick.x >= JOY_UPPER_THRESHOLD && snake.vx != -1) {
    snake.vx = 1;
    snake.vy = 0;
  }
  else if (joystick.x <= JOY_LOWER_THRESHOLD && snake.vx != 1) {
    snake.vx = -1;
    snake.vy = 0;
  }
  else if (joystick.y <= JOY_LOWER_THRESHOLD && snake.vy != -1) {
    snake.vx = 0;
    snake.vy = 1;
  }
  else if (joystick.y >= JOY_UPPER_THRESHOLD && snake.vy != 1) {
    snake.vx = 0;
    snake.vy = -1;
  } 
}


void updateGame() {
  // Updates snake position every tick according to TICK_RATE
  if (currentMillis - startMillis > TICK_RATE) {
    startMillis = millis();
    updateSnake();
    updateMatrix(fruitCoords, HIGH);  // Prevents fruit from disappearing if it spawns inside the snake's tail
    detectCollision();
  }
  currentMillis = millis();
}

void updateSnake() {
  updateMatrix(tail_ptr->coords, LOW);
  if (snake.size > 1) {
    moveTailToFront();
  }
  updateSnakePosition();
  updateMatrix(head_ptr->coords, HIGH);
  
  if (isHeadCollidingWithFruit()) {
    eatFruit();    
  }
}

void moveTailToFront() {  // Set current tail to be the next head by moving pointers to head and tail
  SnakePart *tmp = head_ptr;
  head_ptr = tail_ptr;
  tail_ptr = tail_ptr->next_ptr;
  tmp->next_ptr = head_ptr;
  head_ptr->next_ptr = NULL;
  head_ptr->coords.x = tmp->coords.x;
  head_ptr->coords.y = tmp->coords.y;  
}

void updateSnakePosition() {
  // Moves snake 1 LED in the direction indicated by vx and vy
  // The snake jumps to the other side of the LED-matrix when moving past the borders of the LED-matrix
  head_ptr->coords.x + snake.vx == -1 ? head_ptr->coords.x = MATRIX_WIDTH-1 : head_ptr->coords.x = (head_ptr->coords.x + snake.vx) % MATRIX_WIDTH;
  head_ptr->coords.y + snake.vy == -1 ? head_ptr->coords.y = MATRIX_HEIGHT-1 : head_ptr->coords.y = (head_ptr->coords.y + snake.vy) % MATRIX_HEIGHT;   
}

void updateMatrix(Coords coords, bool value) {
  Display.setPoint(coords.x, coords.y, value); 
}

void addSnakePart() {
  snake.size++;
  SnakePart *newPart = new SnakePart;
  // Set position of new part to tail position
  newPart->coords.x = tail_ptr->coords.x;
  newPart->coords.y = tail_ptr->coords.y;

  // Set the tail to be the new part
  newPart->next_ptr = tail_ptr;
  tail_ptr = newPart;
}

void eatFruit() {
  addSnakePart();
  score++;
  spawnFruit();
}

void spawnFruit() {  // Spawns fruit at a random position
  fruitCoords.x = random(8);
  fruitCoords.y = random(8);
  updateMatrix(fruitCoords, HIGH);
}

void detectCollision() {
  if (snake.size < 5)  // Snake can't collide with its first 4 body parts
    return;

  // Set pointer to the possible collision part closest to tail   
  SnakePart *possibleCollisionPart_ptr = tail_ptr;
  int currentPart = snake.size;
  if (snake.size % 2 == 0) {
    possibleCollisionPart_ptr = possibleCollisionPart_ptr->next_ptr;
    currentPart--;
  }

  // Check for every second part if the head is colliding with that part (The head can only collide with every second part)
  while (currentPart > 4) {
    if (isHeadCollidingWithBody(possibleCollisionPart_ptr->coords)) {
      gameOver();
      return;
    }
    currentPart-=2;
    possibleCollisionPart_ptr = possibleCollisionPart_ptr->next_ptr->next_ptr;   
  }
}

bool isHeadCollidingWithBody(Coords bodyCoords) {
  return head_ptr->coords.x == bodyCoords.x && head_ptr->coords.y == bodyCoords.y;
}

bool isHeadCollidingWithFruit() {
  return head_ptr->coords.x == fruitCoords.x && head_ptr->coords.y == fruitCoords.y;
}

void gameOver() {
  snake.isDead = true;

}  
