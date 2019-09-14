#include <Arduino.h>

// the pin to use
#define PIN 13

// the time to sleep in milliseconds
#define SLEEP_LENGTH 200

void setup() {
	pinMode(PIN, OUTPUT);
	// connect with the board
	Serial.begin(9600);

	// display information to the user, defines the sentinel
	Serial.println("Project 1 -- Morse Code LED Program");
	Serial.println(
			"This program will translate your message into Morse Code and flash on a LED.");
	Serial.println("");
	Serial.println("Please enter your message or Ctrl-C/Ctrl-Z to exit: ");
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
	delay(SLEEP_LENGTH * 3);
	digitalWrite(PIN, LOW);
	delay(SLEEP_LENGTH);
}

// perform the space or null
void spaceOrNull() {
	delay(SLEEP_LENGTH);
}

// handle the string of dot/dash/space
void handle(const char *stringy) {
	// the user pressed something other than an alpha character or number
	if (NULL == stringy) {
		spaceOrNull();
	} else {
		// iterate over the string until NULL
		while (*stringy) {
			switch (*stringy) {
			case '.':
				dot();
				break;
			case '-':
				dash();
				break;
			case ' ':
			default:
				spaceOrNull();
				break;
			}
			// increment to next character in the string
			stringy++;
		}
	}
}

// the character the user typed
char input;
bool isDone = false;

void loop() {

	while (!isDone) {
		if (Serial.available()) {
			// retrieve the data
			input = Serial.read();

			// debug purposes
			Serial.println(input);

			// 3 and 26 are for Ctrl-C/Ctrl-Z
			if ((int) input == 3 || (int) input == 26) {
				Serial.println(
						"You entered Ctrl-C or Ctrl-Z to exit the program. Goodbye.");
				isDone = true;
			}

			// character pressed is number
			if (isdigit(input)) {

				switch (input) {
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

				switch (input) {
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
					handle("--..");
					break;
				case ' ':
					// 7 spaces
					handle("       ");
					break;
					// do nothing for NL/CR
				case '\n':
				case '\r':
					break;
				default:
					handle(NULL);
				}
			}
		}
	}

	exit(0);
}

