
const int GRE = 8;
const int YEL = 10;
const int RED = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(GRE, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(RED, OUTPUT);
  Serial.begin(9600);

}



void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Stop");
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, LOW);  
  digitalWrite(RED, HIGH);
  delay(1500);
  digitalWrite(YEL, HIGH);
  delay(2000);
  Serial.println("Go");
  digitalWrite(RED, LOW);
  digitalWrite(YEL, LOW);
  digitalWrite(GRE, HIGH);
  delay(2000);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRE, LOW);
  delay(2000);

}
