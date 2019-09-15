// library to handle time-based interrupts 
#include <TimerOne.h>

// the reported temperature
float temperature = 0.0;

// the average temperature from the sensor
float averageTemperature = 0.0;

// reading output the sensor
int voltage = 0;

unsigned long time;

// used to exit the program on user input
bool done = false;

void readTemperature() {

  // obtain an average from the sensor so that we have a better reading 
  averageTemperature = 0;
  for (int i = 1; i <= 5; i++){
    // read off the sensor
    voltage = analogRead(A0);
    averageTemperature =  averageTemperature + ( ( (voltage / 204.8) - 0.5) / 0.01);
    delay(15);
  }

  //compute the average value
  temperature = averageTemperature / 5;
}


void setup() {
  Serial.begin(9600);
  
  // display a message to the user
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
   
  // used for reading data from the serial monitor
  char input;
 
  // check to see if the user typed anything
  if (Serial.available()) {     
   
    // read the character
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
   
  // capture the time and covert to seconds
  time = millis() / 1000;
 
  // display time, temp in Fahrenheit
  Serial.print(time); 
  Serial.print(" , ");
  // Celsius to Fahrenheit
  Serial.println((temperature * 9 / 5) + 32);   
}

void loop() {

  // upon startup, we should wait 30 seconds to allow for the temperature sensor to normalize and adjust
  delay(1000 * 30);

  while (!done) {
    // display time/temp
    displayTimeAndTemperature();

    // determine if we should exit 
    handleUserInput();

    // delay 10 seconds
    delay(1000 * 10);  
  }

  exit(0);
}
