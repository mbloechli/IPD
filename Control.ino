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

JrkG2I2C jrk;
int forwardPin = 5;
int backwardPin = 6;
int motorPin = 7;
int potentioPin = A0;
int potentioGND = 4;

  int forwardState = 0;
  int backwardState = 0;
  int motorState = 0;
  int direction = 0;
  int speed = 0;
  int potentioVoltage = 0;

void setup()
{
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(backwardPin, INPUT_PULLUP);
  pinMode(motorPin, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  // Set up I2C.
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  Serial.println("#");
  // read switch values
  forwardState = !digitalRead(forwardPin);
  backwardState = !digitalRead(backwardPin);
  motorState = !digitalRead(motorPin);

  // define direction
  direction = 0;
  if(forwardState) {direction = 1; Serial.print("forward");}
  if(backwardState) {direction = -1; Serial.print("back");}

  // define motor speed
  // read potentiometer Voltag [0 - 1023]
  potentioVoltage = analogRead(potentioPin);
  Serial.print(potentioVoltage);
  //int outputSpeed = potentioVoltage / 1023 * 2047;
  //Serial.print(outputSpeed);


  speed = 0;
  if(motorState) {speed = 2047; Serial.print("running");}


  // send target speed
  jrk.setTarget(2048 + direction * speed);

  delay(100);
}
