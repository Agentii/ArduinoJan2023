#include <LiquidCrystal.h>


char RPin = 6;
char GPin = 9;
char BPin = 10;
char tempPin = A0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

//exercise 9 and 10
  pinMode(tempPin,INPUT);
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);

  Serial.begin(2000000);

// exercise 11:
  lcd.begin(16, 2);

}

void loop() {

  // This section is for exercise 9 and 10
  int valT = analogRead(A0);
  int temp = (valT*5)/10;
  Serial.println(temp);


  if(temp > 28){ 
    digitalWrite(RPin,255); 
    digitalWrite(GPin,0); 
    digitalWrite(BPin,0);}
  else if (temp < 26){ 
    digitalWrite(RPin,0); 
    digitalWrite(GPin,0); 
    digitalWrite(BPin,255);
  } else  {
    digitalWrite(RPin,0); 
    digitalWrite(GPin,255); 
    digitalWrite(BPin,0);
    }

// this section is for exercise 11

    if(temp > 30){      
    lcd.clear();
    lcd.print("hot ");
    }else {      
    lcd.clear();
    lcd.print("Temperature:");
    lcd.setCursor(0, 2);
    lcd.print(temp);
    lcd.print("C");
    lcd.print(char(223));
    }

    delay(1000);

}
