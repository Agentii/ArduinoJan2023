const int GRE = 8;
const int YEL = 10;
const int RED = 12;
int k = 0;

void setup() {
  pinMode(GRE, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(RED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
/*
  // Binary Counter
  
  Serial.println("0");
  Serial.flush();
  digitalWrite(RED, LOW);
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, LOW);
  delay(500);

  Serial.println("1");
  Serial.flush();
  digitalWrite(RED, HIGH);
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, LOW);
  delay(500);

  Serial.println("2");
  Serial.flush();
  digitalWrite(RED, LOW);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRE, LOW);
  delay(500);

  Serial.println("3");
  Serial.flush();
  digitalWrite(RED, HIGH);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRE, LOW);
  delay(500);

  Serial.println("4");
  Serial.flush();
  digitalWrite(RED, LOW);
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, HIGH);
  delay(500);
  
  Serial.println("5");
  Serial.flush();
  digitalWrite(RED, HIGH);
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, HIGH);
  delay(500);
  
  Serial.println("6");
  Serial.flush();
  digitalWrite(RED, LOW);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRE, HIGH);
  delay(500);
  
  Serial.println("7");
  Serial.flush();
  digitalWrite(RED, HIGH);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRE, HIGH);
  delay(500);
*/

  // Binary counter Modulus
  k += 1;

  if(k==8){
    k = 0;
  }

  if(k%2==1) {digitalWrite(RED, HIGH);} else {digitalWrite(RED, LOW);}
  if(k%4>1) {digitalWrite(YEL, HIGH);} else {digitalWrite(YEL, LOW);}
  if(k%8>3) {digitalWrite(GRE, HIGH);} else {digitalWrite(GRE, LOW);}

  delay(1000);
}
