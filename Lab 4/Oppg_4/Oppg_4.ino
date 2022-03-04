#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];
int positions;

void sensorsCalibrate(){
  display.clear();
  delay(1000);
  while (millis()<5000){
    motors.setSpeeds(200, -200);
    lineSensors.calibrate();
    delay(2);
  }
  motors.setSpeeds(0, 0);
}

void setup() {
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  buttonA.waitForButton();
  sensorsCalibrate();
  delay(250);
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to start"));
  buttonA.waitForButton();
  display.clear();
}

int checkSensors(){
  positions = lineSensors.readLine(lineSensorValues);
  display.print(positions);
  return positions;
}

void setMotors(){
  if (positions < 1500){
    motors.setSpeeds(50, 150);
  }
  else if (positions > 2500){
    motors.setSpeeds(150, 50);
  }
  else if (positions > 1500 && positions < 2500){
    motors.setSpeeds(150, 150);
  }
  delay(100);
}

void loop() {
  checkSensors();
  setMotors();
}
