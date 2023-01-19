const int buttonPin = 2;    
const int led1 = 12;     
const int led2 = 11;     
const int led3 = 10;     
const int led4 = 9;     
const int led5 = 8;      

int currentLed = 1;     
int point = 0;
int fail = 0;         

void setup() {
  // set the LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  // set the button pin as input with a pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // make interrupt on button pres and attach it to the function
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, FALLING);
}

void loop() {



  if (fail > 0){                 // To overwrite the normal loop and make all LED turn off
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    delay(1000);
    
    fail = 0;
  } else {

  if (point == 10) {             // the different "levels"/stages of the program
    WinWinWin();    
  } else if (point > 7) {
    LEDRandom();
  } else {
    LEDSequence();
  }
  }
  
}

void LEDSequence () {        // the first 7 points of the game
  

  // turn all the LEDs off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);


  if (currentLed == 1) {
    digitalWrite(led1, HIGH);
  } else if (currentLed == 2) {
    digitalWrite(led2, HIGH);
  } else if (currentLed == 3) {
    digitalWrite(led3, HIGH);
  } else if (currentLed == 4) {
    digitalWrite(led4, HIGH);
  } else if (currentLed == 5) {
    digitalWrite(led5, HIGH);
  }
  
  
  // move to the next LED in the sequence
  currentLed++;
  
  // reset the sequence if all the LEDs have been lit up
  if (currentLed > 5) {
    currentLed = 1;
  }

  delay(500);

}

void LEDRandom () {     // after 8 point of the game
  
  // turn all the LEDs off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);

  currentLed = random(1, 6);

  if (currentLed == 1) {
    digitalWrite(led1, HIGH);
  } else if (currentLed == 2) {
    digitalWrite(led2, HIGH);
  } else if (currentLed == 3) {
    digitalWrite(led3, HIGH);
  } else if (currentLed == 4) {
    digitalWrite(led4, HIGH);
  } else if (currentLed == 5) {
    digitalWrite(led5, HIGH);
  }

  delay(500);
}

void WinWinWin () {            // if you win the game!
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(500);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  delay(1000);

  point = 0;

}

void buttonPress() {       // the button press function


  if (point < 9 && currentLed == 4) {
    // score a point
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);

    point++;

  } else if (point > 7 && currentLed == 3) {
    // score a point
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);

    point++;

  } else {
    // if you miss the middle LED
      fail++;
  }

  


}
