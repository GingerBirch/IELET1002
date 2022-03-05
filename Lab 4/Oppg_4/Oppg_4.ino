#include <Zumo32U4.h> // inkluderer Zumo-biblioteket

Zumo32U4ButtonA buttonA;         // deklarerer knapp A
Zumo32U4LCD display;             // deklarerer LCD-skjerm
Zumo32U4Motors motors;           // deklarerer motorene
Zumo32U4LineSensors lineSensors; // deklarerer linjesensorene

#define NUM_SENSORS 5                       // definerer hvor mange sensorer det er
unsigned int lineSensorValues[NUM_SENSORS]; // lager liste med lengde likt antall sensorer
int16_t lastError = 0;                      // deklarerer siste avstand fra teip
const uint16_t maxSpeed = 400;              // deklarerer maks fart

// funksjon som kalibrerer linjesensorene
void sensorsCalibrate(){
  display.clear(); // fjerner alt fra LCD-skjerm
  delay(1000); // venter 1 sekund for å få fjernet fingeren fra knappen
  unsigned long calibrateTime = millis() + 2000; // lagrer hvor lenge Zumo skal kalibreres
  while (millis() < calibrateTime){
    motors.setRightSpeed(maxSpeed); // setter høyrehjulet til maks fart
    lineSensors.calibrate(); // kalibrerer linjesensorene
  }
  motors.setRightSpeed(0); // stopper Zumo
}

void setup() {
  lineSensors.initFiveSensors(); // konfigurerer Zumo til å bruke alle fem sensorer
  display.clear();
  display.print(F("Press A")); // printer melding til LCD-skjerm
  display.gotoXY(0, 1); // flytter markøren en linje ned
  display.print(F("to calib"));
  buttonA.waitForButton(); // setter programmet på pause til knappen trykkes
  
  sensorsCalibrate(); // kjører kalibrering
  lineSensors.readCalibrated(lineSensorValues); // leser de kalibrerte verdiene til sensorene

  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to start"));
  buttonA.waitForButton();
  display.clear();
}

// funksjon som setter motorene til en hviss fart
void setMotors(){
  int16_t position = lineSensors.readLine(lineSensorValues); // tar inn posisjonen i forhild til teipen
  int16_t error = position - 2000; // lagrer hvor langt Zumo er fra teipen
  int16_t speedDifference = error / 4 + 6 * (error - lastError); // regner ut hastighetsforskjellen til hjulene

  lastError = error; // lagrer forrige avstand fra teipen

  // legger til maksfart +- hastighetsforskjellen
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // hindrer farten i å overstige maks fart
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  // setter hastighetene til hjulene
  motors.setSpeeds(leftSpeed, rightSpeed);
}

// kjører motor-funksjonen hele tiden
void loop() {
  setMotors();
}
