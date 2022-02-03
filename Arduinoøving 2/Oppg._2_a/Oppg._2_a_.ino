const int potPin = A0; // Pin til potensiometer
float potValue; // Variabel for verdien til potensiometeret

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT); // Tar input fra potensimeteret
  Serial.begin(9600); // Åpner serialporten, setter data rate til 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin); // Leser av potensiometeret og lagrer verdien
  Serial.println(potValue);
}
