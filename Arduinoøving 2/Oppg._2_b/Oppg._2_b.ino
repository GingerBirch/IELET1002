const int potPin = A0; // Pin til potensiometer
float potValue; // Variabel for verdien til potensiometeret
float voltage; // Variabel for spenningen lest på potensiometeret
float resistance; // Variabel for motstanden spenningen leses over

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT); // Tar input fra potensimeteret
  Serial.begin(9600); // Åpner serialporten, setter data rate til 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin); // Leser av potensiometeret og lagrer verdien
  voltage = potValue * 5 / 1023; // Regner ut spenningsverdien lest på potensiometeret
  resistance = potValue / 1023 * 10000; // Regner ut verdien til motstanden i potensiometeret
  Serial.println(resistance);
}
