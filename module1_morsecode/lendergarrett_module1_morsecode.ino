// the pin to use
#define PIN 13

// the time to sleep in milliseconds
#define SLEEP_LENGTH 300

void setup() {
  pinMode(PIN, OUTPUT);
  // connect with the boared
  Serial.begin(9600);
}

// the character the user typed
char input;

void loop() {
  if (Serial.available()) {
    // retrieve the data
    input = Serial.read();

    // debug purposes
    Serial.println(input);

    // character pressed is number
    if (isdigit(input)) {

      switch(input) {
        case '1': 
          handle(".----");
          break;
        case '2': 
          handle("..---");
          break;
        case '3': 
          handle("...--");
          break;
        case '4': 
          handle("....-");
          break;
        case '5': 
          handle(".....");
          break;
        case '6':
          handle("-....");
          break;
        case '7':
          handle("--...");
          break;
        case '8':
          handle("---..");
          break;
        case '9':
          handle("----.");
          break;
        case '0':
          handle("-----");
          break;
        default:
          handle(NULL);
      }
      // character pressed is letter or space
    } else {
        input = toupper(input);
  
        switch(input) {
          case 'A':
            handle(".-");
            break;
          case 'B':
            handle("-...");
            break;
          case 'C':
            handle("-.-.");
            break;
          case 'D': 
            handle("-..");
            break;
          case 'E':
            handle(".");
            break;
          case 'F': 
            handle("..-.");
            break;
          case 'G': 
            handle("--.");
            break;
          case 'H':
            handle("....");
            break;
          case 'I': 
            handle("..");
            break;
          case 'J': 
            handle(".---");
            break;
          case 'K': 
            handle("-.-");
            break;
          case 'L': 
            handle(".-..");
            break;
          case 'M': 
            handle("--");
            break;
          case 'N': 
            handle("-.");
            break;
          case 'O': 
            handle("---");
            break;
          case 'P': 
            handle(".--.");
            break;
          case 'Q': 
            handle("--.-");
            break;
          case 'R': 
            handle(".-.");
            break;
          case 'S': 
            handle("...");
            break;
          case 'T': 
            handle("-");
            break;
          case 'U': 
            handle("..-");
            break;
          case 'V': 
            handle("...-");
            break;
          case 'W': 
            handle(".--");
            break;
          case 'X': 
            handle("-..-");
            break;
          case 'Y': 
            handle("-.--");
            break;
          case 'Z': 
            handle("--.." );
            break;
          case ' ': 
            handle("  ");
            break;
          default:
            handle(NULL);
      }
    }
  }
}

// perform the dot
void dot() {
  digitalWrite(PIN, HIGH);
  delay(SLEEP_LENGTH);
  digitalWrite(PIN, LOW);
  delay(SLEEP_LENGTH);
}

// perform the dash
void dash() {
  digitalWrite(PIN, HIGH);
  delay(SLEEP_LENGTH*3);
  digitalWrite(PIN, LOW);
  delay(SLEEP_LENGTH);
}

// perform the space or null
void spaceOrNull() {
  delay(SLEEP_LENGTH);
}

// handle the string of dot/dash/space
void handle(const char* stringy) {
  // the user pressed something other than an alpha character or number
  if (NULL == stringy) {
    spaceOrNull();
  } else {
    // iterate over the string until NULL
    while(*stringy) {
      switch(*stringy) {
        case '.':
          dot();
          break;
        case '-':
          dash();
          break;
        case ' ': 
          spaceOrNull();
          break;
        default:
          spaceOrNull();
          break;
      }
      // increment to next character in the string
      stringy++;
    }
  }
}
