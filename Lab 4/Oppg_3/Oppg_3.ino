#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

unsigned long calibrateTime = 0;
const uint16_t maxSpeed = 400;
int16_t lastError = 0;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

void sensorsCalibrate(){
  display.clear();
  delay(1000);
  calibrateTime = millis() + 2000;
  while (millis() < calibrateTime){
    motors.setRightSpeed(400);
    lineSensors.calibrate();
    delay(2);
  }
  motors.setRightSpeed(0);
}

void setup() {
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  buttonA.waitForButton();
  sensorsCalibrate();
  display.print("Finished");
}

void loop() {
  /*
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);*/
}
