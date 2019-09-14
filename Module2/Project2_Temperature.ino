#include <TimerOne.h>

float temperature = 0.0;
float averageTemperature = 0.0;
int voltage = 0;

unsigned long time;
bool done = false;

void readTemperature() {
  averageTemperature = 0;
  for (int i = 1; i <= 5; i++){
    voltage = analogRead(A0);
    averageTemperature =  averageTemperature + ( ( (voltage / 204.8) - 0.5) / 0.01);
    delay(15);
  }

  //compute the average value
  temperature = averageTemperature / 5;
}


void setup() {
  Serial.begin(9600);
  
  // Show a welcome message as human-readable ASCII text
  Serial.println("Project 2 Serial Transmit of Temperature");
  Serial.println("This program transmits the time and temp at a periodic rate of around 10s");
  Serial.println("across a Serial bus like USB to the Host. ");
  Serial.println("");
  Serial.println("Press !, Ctrl-C, or Ctrl-Z to end the program");
  Serial.println("");
  Serial.println("Temperature will be recorded every 10 seconds");
  Serial.println("");
  Serial.println("The results will be given in the following format: ");
  Serial.println("TIME, TEMP IN FAHRENHEIT");
 
  /*
   * Set the interrupt timer to 10 seconds
   * 1000 microseconds is 1 millisecond 
   * 1000 * 1000 -> 1 second 
   * 1000 * 1000 * 10 -> 10 seconds
   */
  Timer1.initialize(1000 * 1000 * 10);
 
  // attach the timer so that readTemperature will be run on each timer interrupt
  Timer1.attachInterrupt(readTemperature); 
}

void handleUserInput() {
   
  // Used for reading data from the serial monitor
  char input;
 
  // Check to see if ! is available to be read
  if (Serial.available()) {     
   
    // Read the character
    // Serial.read() returns the first (oldest) character in the buffer 
    // and removes that byte of data from the buffer
    input = Serial.read();    
 
    // program should be stopped if the user types !, Ctrl-C, Ctrl-Z
    // 3 and 26 are for Ctrl-C/Ctrl-Z
    if (input == '!' || (int) input == 3 || (int) input == 26) {
      done = true;  
      Serial.println("Temperature recording has finished. Goodbye.");
    }
  }    
}

void displayTimeAndTemperature() {
   
  // Capture the time and covert to seconds
  time = millis() / 1000;
 
  // display time, temp in Fahrenheit
  Serial.print(time); 
  Serial.print(" , ");
  Serial.println((temperature * 9 / 5) + 32);   
}

void loop() {

  delay(1000 * 30);

  while (!done) {
  
    displayTimeAndTemperature();

    handleUserInput();

    // delay 10 seconds
    delay(1000 * 10);  
  }

  exit(0);
}

