#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;

void setup()
{
  display.clear();
  display.print(F("Press A"));
  buttonA.waitForButton();

  display.clear();
}

void loop()
{
  ledRed(1);
  ledYellow(1);
  ledGreen(1);
  buzzer.playFrequency(440, 200, 15);

  for (int speed = 0; speed <= 400; speed++){
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--){
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 0; speed <= 400; speed++){
    motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--){
    motors.setLeftSpeed(speed);
    delay(2);
  }
  
  delay(100);

  ledRed(0);
  ledYellow(0);
  ledGreen(0);
  buzzer.playFrequency(840, 200, 15);

  for (int speed = 0; speed <= 400; speed++){
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--){
    motors.setRightSpeed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--){
    motors.setLeftSpeed(speed);
    delay(2);
  }

  for (int speed = 0; speed <= 400; speed++){
    motors.setLeftSpeed(speed);
    delay(2);
  }

  delay(100);
}
