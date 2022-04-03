const uint8_t potPin = 34;
const uint8_t fotoResPin = 32;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(fotoResPin, INPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  float potVoltage = potValue * 3.3 / 4095;
  Serial.print("Spenning potmeter: ");
  Serial.println(potVoltage);
  
  int fotoResValue = analogRead(fotoResPin);
  float fotoResVoltage = fotoResValue * 3.3 / 4095;
  Serial.print("Spenning fotoresistor: ");
  Serial.println(fotoResVoltage);
  delay(500);
}
