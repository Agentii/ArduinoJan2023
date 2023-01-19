char R = 9;
char G = 10;
char B = 11;
int red, green, blue;


void setup() {
  Serial.begin(2000000);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

}

void loop() {
  
  while(Serial.available() > 0){
    red = Serial.parseInt();
    green = Serial.parseInt();
    blue = Serial.parseInt();
    RGB(red, green, blue);

  }

}


void RGB (int red, int green, int blue){

 if(Serial.read() == '\n'){

   red = 255 - constrain(red, 0, 255);
   green = 255 - constrain(green, 0, 255);
   blue = 255 - constrain(blue, 0, 255);
 }

  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
  fade(red, green, blue);
}



void fade (int red, int green, int blue){

  for(int i = 0; i<255; i++){
  red = constrain(red-1,0,255);
  green = constrain(green-1,0,255);
  blue = constrain(blue-1,0,255);
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
  delay(10);
  }



/*
  for(int i=red; i > 0 ; i--){
    red = red-1;
    analogWrite(R, red);
    delay(10);
  }
  
  for(int i=green; i > 0 ; i--){
    green = green-1;
    analogWrite(G, green);
    delay(10);
  }

  for(int i=blue; i > 0 ; i--){
    blue = blue -1;
    analogWrite(B, blue);
    delay(10);
  }*/

}


