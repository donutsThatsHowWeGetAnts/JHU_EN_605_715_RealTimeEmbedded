/*
 * Design and other useful information to create this sytem was found at the following sites:
 * 
 * https://www.raspberrypi.org/forums/viewtopic.php?t=205523
 * https://automaticaddison.com/how-to-develop-an-arduino-based-optical-tachometer/
 * https://www.how2electronics.com/digital-tachometer-using-ir-sensor-with-arduino/
 */

// fan blade and motor pin
const unsigned int MOTOR_PIN = 3;
 
// IR LED pin
const unsigned int IR_LED = 13;
 
// blades on the propeller
const unsigned int BLADE_COUNT = 3;
 
// volatile since used within ISR
volatile unsigned int break_number = 0;
 
bool done = false;
unsigned long time;
unsigned int rpm;
 
void setup() {
 
  Serial.begin(9600);
 
  // Show a welcome message as human-readable ASCII text
  Serial.println("Project 3 Measure and Transmit Fan Speed and Thrust");
  Serial.println("This program transmits the time and RPM of a propeller.");
  Serial.println("");
  Serial.println("Press !, Ctrl-C, or Ctrl-Z to end the program");
  Serial.println("");
  Serial.println("Enter the speed of the motor (between 100 and 255)");
  Serial.println("");
  Serial.println("The time and RPMs will be recorded in the following way:");
  Serial.println("TIME, RPM");
 
  // IR phototransistor connected to pin 2, breaks when going from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(2), isr_break_count, FALLING); 
 
  // turn on the IR LED
  pinMode(IR_LED, OUTPUT);
  digitalWrite(IR_LED, HIGH);
 
  // enable output for the motor
  pinMode(MOTOR_PIN, OUTPUT);
 
  break_number = 0;
  rpm = 0;  
  
}
 
void loop() {
 
  display_time_and_rpm();
   
  start_motor();
 
  while(!done) {    
 
    // Update time and rpm every second
    delay(1000);
 
    // Don't process interrupts during this calculation
    noInterrupts();
 
    // Calculate the RPM. If a 3-blade propeller, 3 breaks
    // per second would yield 1 rpm, which is 60 rpm. 
    rpm = (60 * break_number) / BLADE_COUNT;
 
    // Display the time and rpm
    display_time_and_rpm();
 
    // End program if sentinel is entered 
    end_program();    
     
    break_number = 0;
    rpm = 0;
 
    // Restart interrupts
    interrupts();
  }
   
  exit(0);
}

void start_motor() {
 
  // Wait for the user to enter the speed of the motor
  while (Serial.available() == 0){};
 
  // Activate the motor
  int speed = Serial.parseInt();
  if (speed >= 100 && speed <= 255) {
    analogWrite(MOTOR_PIN, speed);
  }
}
 
/*
 * ISR
 * This function counts the number of interrupts
 */
void isr_break_count() {
  break_number++;
}

void display_time_and_rpm() {
   
  // get the time
  time = millis() / 1000;
 
  // display Time, RPMs
  Serial.print(time); 
  Serial.print(" , ");
  Serial.println(rpm);   
}
 
/**
  * This function ends the program
  */
void end_program() {
   
  char input;
 
  // check for user input
  if (Serial.available()) {     
   
    // Read the character
    input = Serial.read();
 
    // program should be stopped if the user types !, Ctrl-C, Ctrl-Z
    // 3 and 26 are for Ctrl-C/Ctrl-Z
    if (input == '!' || (int) input == 3 || (int) input == 26) {
      done = true;  
 
      // turn off the motor
      analogWrite(MOTOR_PIN, 0);
 
      // turn off the IR LED
      digitalWrite(IR_LED, LOW);
       
      Serial.println("Completed recording Time/RPMs.");
    }
  }    
}
