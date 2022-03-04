#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
int16_t lastError = 0;
const uint16_t maxSpeed = 400;

void sensorsCalibrate(){
  display.clear();
  delay(1000);
  for (int i = 0; i < 120; i++){
    motors.setSpeeds(200, -200);
    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

void setup() {
  lineSensors.initFiveSensors();
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  buttonA.waitForButton();
  
  sensorsCalibrate();
  lineSensors.readCalibrated(lineSensorValues);

  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to start"));
  buttonA.waitForButton();
  display.clear();
}

void setMotors(){
  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

void loop() {
  setMotors();
}
