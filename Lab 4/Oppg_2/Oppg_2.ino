#include <Wire.h>
#include <Zumo32U4.h> // Inkluderer Zumo-biblioteket

Zumo32U4ButtonA buttonA; // deklarerer knapp A
Zumo32U4LCD display;     // deklarerer LCD-skjerm 
Zumo32U4Buzzer buzzer;   // deklarerer piezo-buzzer
Zumo32U4Motors motors;   // deklarerer motorene

void setup()
{
  display.clear();              // fjerner alt fra LCD som er fra før
  display.print(F("Press A"));  // printer melding
  buttonA.waitForButton();      // funksjon som holder programmet på pause frem til knappen trykkes
  display.clear();
}

// justerer for-løkker og delay'er slik at Zumo kjører i én loop

// funksjon for blinking av LED
void led_blink(){
  // setter LED på
  ledRed(1);
  ledYellow(1);
  ledGreen(1);
  delay(100);
  // setter LED av
  ledRed(0);
  ledYellow(0);
  ledGreen(0);
  delay(100);
}

// funksjon som får Zumo til å kjøre i et åttetall
void aatteTall(){
  for (int i = 0; i < 6; i++){
    motors.setSpeeds(200, 0); // setter venstrehjulet til å kjøre
    buzzer.playFrequency(440, 200, 15); // spiller av en lyd fra piezo-buzzer (frekvens, lengde, volum)
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0); // stopper begge hjul
  for (int i = 0; i < 6; i++){
    motors.setSpeeds(0, 200); // setter høyrehjulet til å kjøre
    buzzer.playFrequency(440, 200, 15);
    led_blink();
    buzzer.playFrequency(840, 200, 15);
    led_blink();
  }
  motors.setSpeeds(0, 0);
}

// funksjon som får Zumo til å kjøre i sirkel
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

// funksjon som får Zumo til å kjøre i sirkel andre veien
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

// kjører de forskjellige funksjonene med en liten pause imellom
void loop()
{
  aatteTall();
  delay(500);
  sirkel();
  delay(500);
  motsattSirkel();
  delay(500);
}
