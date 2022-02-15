const uint8_t EN1 = 11; // Enable
const uint8_t IN1 = 13; // Input 1
const uint8_t IN2 = 12; // Input 2
const int potPin = A0; // Pin for potensiometer
const int tiltPin = 7; // Pin for tilmåler

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(tiltPin, INPUT);
}

void loop() {
  int potVal = analogRead(potPin); // Leser verdien til potensiometeret
  int tiltVal = digitalRead(tiltPin); // Leser verdien til tiltmåleren
  float rpm = map(potVal, 0, 1023, -250, 250); // Konverterer lyssensorverdiene til verdien for motoren

  // Hvis motorverdien er over 0 og det går strøm gjennom tiltmåleren
  if (rpm > 0 && tiltVal == HIGH){
    // Motoren roterer mot høyre
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, rpm); // Skriver absoluttveriden av motorverdien til motoren
  }
  // Hvis motorverdien er under 0 og det går strøm gjennom tiltmåleren
  else if (rpm < 0 && tiltVal == HIGH){
    // Motoren roterer mot venstre
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, abs(rpm)); // Skriver absoluttveriden av motorverdien til motoren
  }
  // Hvis motorverdien er lik 0 eller det ikke går strøm gjennom tiltmåleren
  else{
    analogWrite(EN1, 0);
  }
}
