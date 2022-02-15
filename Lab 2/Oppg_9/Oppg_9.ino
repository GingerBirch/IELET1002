#include <Servo.h> // Inkluderer servomotor-biblioteket

const uint8_t EN1 = 11; // Enable
const uint8_t IN1 = 13; // Input 1
const uint8_t IN2 = 12; // Input 2
const int potPin = A0; // Pin for lyssensor
const int tiltPin = 7; // Pin for tiltmåler
const int servoPin = 9; // Pin til servomotoren
Servo servo;

void setup() {
  servo.attach(servoPin); // Kobler servomotoren opp mot dens pin
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(tiltPin, INPUT);
}

void loop() 
  int potVal = analogRead(potPin); // Leser verdien til lyssensoren
  int tiltVal = digitalRead(tiltPin); // Leser verdien til tilten
  float rpm = map(potVal, 0, 511, -250, 250); // Konverterer lyssensorverdiene til verdier for motoren
  int servoValNeg = map(potVal, 0, 255, -180, 0); // konverterer lyssensorvrdiene til verdier for servoen
  int servoValPos = map(potVal, 256, 511, 0, 180);  // konverterer lyssensorvrdiene til verdier for servoen

  // Hvis motorverdien er over 0 og det går strøm gjennom tiltmåleren
  if (rpm > 0 && tiltVal == HIGH){
    // Motoren roterer mot høyre
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, rpm); // Skriver absoluttverdien til motoren
    servo.write(servoValPos); // Skriver farten til servomotoren
  }
  // Hvis motorverdien er under 0 og det går strøm gjennom tiltmåleren
  else if (rpm < 0 && tiltVal == HIGH){
    // Motoren roterer mot venstre
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, abs(rpm)); // Skriver absoluttverdien til motoren
    servo.write(abs(servoValNeg)); // Skriver farten til servomotoren
  }
  // Hvis motorverdien er lik 0 eller det ikke går strøm gjennom tiltmåleren
  else{
    analogWrite(EN1, 0);
  }
}
