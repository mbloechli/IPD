// This example shows how to control the Jrk G2 over I2C by
// sending Set Target commands.
//
// The Jrk's input mode must be set to "Serial/I2C/USB".  The
// Jrk's device number must be set to its default value of 11.
//
// Please see https://github.com/pololu/jrk-g2-arduino for
// details on how to make the connections between the Arduino and
// the Jrk G2.

#include <JrkG2.h>

// Initialize JrkG2 control
JrkG2I2C jrk;

// Define Pins
int forwardPin = 5;
int backwardPin = 6;
int activationPin = 7;
int potentioPin = A0;

// Initialize Parameters
int direction = 0;
int speed = 0;
int potentioVoltage = 0;

// Define System Parameters
const int topSpeed = 600;  // Define your target speed
const int minSpeed = 180; // Define minimum speed to overcome motor friction

void setup()
{
  // Initialize Pins
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(backwardPin, INPUT_PULLUP);
  pinMode(activationPin, INPUT_PULLUP);

  // Set up I2C.
  Wire.begin();

  // Set up Serial Connection
  Serial.begin(9600);
}

void loop()
{  
  // Read Potentio Voltage
  potentioVoltage = analogRead(potentioPin);

  // Check if motor is activated
  if(!digitalRead(activationPin)){

    // Check in which direction the motor should move
    direction = 0;
    if(!digitalRead(forwardPin)) { direction = -1; }
    if(!digitalRead(backwardPin)) { direction = 1; }

    // Calculate speed
    
    speed = direction * map(potentioVoltage, 0, 1023, topSpeed, minSpeed);
    
  } else{
    speed = 0;
  }

  // Send speed to motor driver
  jrk.setTarget(2048 + speed);

  // Send debug information over serial connection
  Serial.print(" Potentio Voltage: ");
  Serial.print(potentioVoltage);
  Serial.print(", Speed: ");
  Serial.print(speed);
  Serial.print(", Direction: ");
  Serial.println(direction);
}
