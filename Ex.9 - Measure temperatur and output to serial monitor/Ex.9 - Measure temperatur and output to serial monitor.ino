

void setup() {
  pinMode(A0,INPUT);

  Serial.begin(2000000);

}

void loop() {
  int valT = analogRead(A0);
  double voltage = (valT/1024.0)*5;
  int temp = (valT*5)/10;

  Serial.println(voltage);
  Serial.println(temp);


}
