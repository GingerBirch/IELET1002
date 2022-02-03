const int potPin = A0; // Pin til potensiometer

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT); // Tar input fra potensimeteret
  Serial.begin(9600); // Åpner serialporten, setter data rate til 9600 bps
}

int assign(float x) {
  return (round(x * 3 / 1023));
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(potPin); // Leser av potensiometeret og lagrer verdien
  int value = assign(potValue);
  Serial.print("range ");
  Serial.println(value);  
  delay(100);
}
