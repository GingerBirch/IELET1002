const int ledPin = 6;
int brightness = 0; // Variabel for lysverdien
int count = 15; // Hvor mye lysverdien endres hvert steg
int increase = true;

void setup() {
pinMode(ledPin, OUTPUT);
}

void loop() {
// Øker lysverdien jevnt opp til maksverdi
while (increase == true){
  analogWrite(ledPin, brightness);
  brightness = brightness + count;
  if (brightness == 255){ // Ved maks lysverdi
    increase = false;
  }
  delay(100);
}
// Senker lysverdien jevnt ned til minimalverdi
while (increase == false){
  analogWrite(ledPin, brightness);
  brightness = brightness - count;
  if (brightness == 0){ // Ved minimal lysverdi
    increase = true;
  }
  delay(100);
}
}
