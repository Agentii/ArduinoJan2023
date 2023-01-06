void setup() {
}

void loop() {
}


// 17.2
struct animal {
  int age;
  string "gender";
  double weight;
  double height;
  bool alive;
  int = ID;

}

// 17.3

struct animal abe;
abe.age = 55;
abe.gender = "male";
abe.weight = 102.2;
abe.height = 44.3;
abe.alive = false;
abe.ID = 0;

struct animal hest;
hest.age = 23;
hest.gender = "female";
hest.weight = 245.4;
hest.height = 175.7;
hest.alive = true;
hest.ID = 0;


// 17.3
void printAnimal (struct animal a){
    Serial.print("age; ");
    Serial.println(a.age);
    Serial.print("gender; ");
    Serial.print(a.gender);
    Serial.print("weight; ");
    Serial.print(a.weight);
    Serial.print("height; ");
    Serial.print(a.height);
    Serial.print("alive; ");
    Serial.print(a.alive);    
}

//17.4

void swapWeight (struct animal *a, struct animal *b) {
  double TMP = *a.weight;
  *a.weight = *b.weight;
  *b.weight = TMP;
}

// 17.5

void compareAnimals (struct animal a, struct animal b) {
  if (a.weight < b.weight){
    a.ID = 1;
    b.ID = 2;
  } else {
    b.ID = 1;
    a.ID = 2;
  }

}




