/* This example shows how to blink the three user LEDs
on the Zumo 32U4. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
Zumo32U4LCD display;
Zumo32U4Buzzer buzzer;

void setup()
{
  display.clear();
  display.print(F("Press A"));
  buttonA.waitForButton();

  display.clear();
}

void loop()
{
  // Turn the LEDs on.
  ledRed(1);
  ledYellow(1);
  ledGreen(1);
  buzzer.playFrequency(440, 200, 15);

  // Wait for a second.
  delay(500);

  // Turn the LEDs off.
  ledRed(0);
  ledYellow(0);
  ledGreen(0);
  buzzer.playFrequency(840, 200, 15);

  // Wait for a second.
  delay(500);
}
