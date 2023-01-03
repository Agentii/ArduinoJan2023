bool state = 0;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(9, INPUT_PULLUP);

  digitalWrite(12, LOW);

  digitalWrite(9, HIGH);


}


void loop() {

  if(!digitalRead(9)){
    while(!digitalRead(9)){
      
    }
    state = 1 - state;
  } 

  digitalWrite(12, state);

}                  
   
