const int potPin = A0; // Pin til potensiometer

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT); // Tar input fra potensimeteret
  Serial.begin(9600); // Åpner serialporten, setter data rate til 9600 bps
}

int range(float x) { // Funksjon for range-tallet
  return (round(x * 3 / 1023)); // Kalkulerer verdien mellom 0 og 3
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin); // Leser av potensiometeret og lagrer verdien
  int value = range(potValue); // Kaller på funksjonen og regner ut range-verdien
  Serial.print("range ");
  Serial.println(value); // Printer range-verdien til Serial Monitor
  delay(100);
}
