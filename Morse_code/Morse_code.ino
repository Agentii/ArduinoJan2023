const int LED = LED_BUILTIN;
const int UNIT = 400;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(2000);  // 2 sec delay before program is repeated
  morseString("SOS");
}

void morseString(String string) {  // Using string instead of char[] for cleaner function calls
  for (char character : string) {
    switch (character) {
    case 'A':
      dot(1);
      line(1);
      break;
    case 'B':
      line(1);
      dot(3);
      break;
    case 'C':
      line(1);
      dot(1);
      line(1);
      dot(1);
      break;
    case 'D':
      line(1);
      dot(2);
      break;
    case 'E':
      dot(1);
      break;
    case 'F':
      dot(2);
      line(1);
      dot(1);
      break;
    case 'G':
      line(2);
      dot(1);
      break;
    case 'H':
      dot(4);
      break;
    case 'I':
      dot(2);
      break;
    case 'J':
      dot(1);
      line(3);
      break;
    case 'K':
      line(1);
      dot(1);
      line(1);
      break;
    case 'L':
      dot(1);
      line(1);
      dot(2);
      break;
    case 'M':
      line(2);
      break;
    case 'N':
      line(1);
      dot(1);
      break;
    case 'O':
      line(3);
      break;
    case 'P':
      dot(1);
      line(2);
      dot(1);
      break;
    case 'Q':
      line(2);
      dot(1);
      line(1);
    case 'R':
      dot(1);
      line(1);
      dot(1);
      break;
    case 'S':
      dot(3);
      break;
    case 'T':
      line(1);
      break;
    case 'U':
      dot(2);
      line(1);
      break;
    case 'V':
      dot(3);
      line(1);
      break;
    case 'W':
      dot(1);
      line(2);
      break;
    case 'X':
      line(1);
      dot(2);
      line(1);
      break;
    case 'Y':
      line(1);
      dot(1);
      line(2);
      break;
    case 'Z':
      line(2);
      dot(2);
      break;
    case '1':
      dot(1);
      line(4);
      break;
    case '2':
      dot(2);
      line(3);
      break;
    case '3':
      dot(3);
      line(2);
      break;
    case '4':
      dot(4);
      line(1);
      break;
    case '5':
      dot(5);
      break;
    case '6':
      line(1);
      dot(4);
      break;
    case '7':
      line(2);
      dot(3);
      break;
    case '8':
      line(3);
      dot(2);
      break;
    case '9':
      line(4);
      dot(1);
      break;
    case '0':
      line(5);
      break;
    case ' ':
      delay(7*UNIT);
      break;
    default:
      break;
    }
  }
}

void dot(int iter) {
  for (int i = 0; i < iter; i++) {
    digitalWrite(LED, HIGH);
    delay(UNIT);
    digitalWrite(LED, LOW);
    delay(3*UNIT);
  }
}

void line(int iter) {
  for (int i = 0; i < iter; i++) {
    digitalWrite(LED, HIGH);
    delay(3*UNIT);
    digitalWrite(LED, LOW);
    delay(3*UNIT);
  }
}
