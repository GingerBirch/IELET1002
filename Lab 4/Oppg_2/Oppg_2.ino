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

void led_on(){
  ledRed(1);
  ledYellow(1);
  ledGreen(1);
}

void led_off(){
  ledRed(0);
  ledYellow(0);
  ledGreen(0);
}

void led_blink(){
    led_on();
    delay(100);
    led_off();
    delay(100);
}

void aatteTall(){
  for (int i = 0; i < 6; i++){
    motors.setSpeeds(200, 0);
    buzzer.playFrequency(440, 200, 15);
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0);
  for (int i = 0; i < 6; i++){
    motors.setSpeeds(0, 200);
    buzzer.playFrequency(440, 200, 15);
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0);
}

void sirkel(){
  for (int i = 0; i < 9; i++){
    motors.setSpeeds(200, 50);
    buzzer.playFrequency(440, 200, 15);
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0);
}

void motsattSirkel(){
  for (int i = 0; i < 9; i++){
    motors.setSpeeds(50, 200);
    buzzer.playFrequency(440, 200, 15);
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0);
}

void loop()
{
  aatteTall();
  delay(500);
  sirkel();
  delay(500);
  motsattSirkel();
  delay(500);
}
