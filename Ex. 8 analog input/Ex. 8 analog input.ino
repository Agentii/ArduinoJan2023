int val;
float red, green, blue;
char R = 9;
char G = 10;
char B = 11;

void setup() {
  Serial.begin(2000000);
  pinMode(A0 , INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

}

void loop() {

  val = analogRead(A0);

  float voltage= val * (5.0 / 1023.0); // this line is to calculate voltage output

  if(val > 512) {
    red = 0;
    blue = 0.4985 * val;
    green = 0.4985 * (512-val);
  } else {
    red = 0.4985 * (1023-val);
    blue = 0;
    green = 0.4985 * (val - 512);
  }
  
  analogWrite(R, red);
  analogWrite(G, green);
  analogWrite(B, blue);

}

