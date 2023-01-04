const int R = 9;
const int G = 10;
const int B = 11;

int red, green, blue;

void setup() {
  Serial.begin(2000000);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

}

void loop() {
  if (Serial.available() == 3) {
    red = Serial.parseInt();
    green = Serial.parseInt();
    blue = Serial.parseInt();
    RGB(red, green, blue);
  }
}


void RGB (int red, int green, int blue) {

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);    
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
  delay(1000);
  fade(red, green, blue);
}

void fade(int red, int green, int blue) {
  delay(10);
  red = constrain(red-1, 0, 255);
  green = constrain(green-1, 0, 255);
  blue = constrain(blue-1, 0, 255);
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);
  if (red + green + blue > 0) {
    fade(red, green, blue);
  }
}

