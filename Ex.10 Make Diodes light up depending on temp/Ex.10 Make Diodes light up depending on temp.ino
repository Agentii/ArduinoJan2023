char RPin = 9;
char GPin = 10;
char BPin = 11;
char tempPin = A0;

void setup() {
  pinMode(tempPin,INPUT);
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);

  Serial.begin(2000000);

}

void loop() {
  int valT = analogRead(A0);
  int temp = (valT*5)/10;
  Serial.println(temp);


  if(temp > 30){ 
    analogWrite(RPin, 255); 
    analogWrite(GPin,0); 
    analogWrite(BPin,0);}
  else if (temp < 25){ 
    analogWrite(RPin,0); 
    analogWrite(GPin,0); 
    analogWrite(BPin,255);}
  else {
    analogWrite(RPin,0); 
    analogWrite(GPin,255); 
    analogWrite(BPin,0);}

}
