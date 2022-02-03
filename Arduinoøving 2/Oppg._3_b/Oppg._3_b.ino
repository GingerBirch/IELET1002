const int ledPin = 6;
const int sensorPin = A0;
float sensorValue;
int brightness;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(sensorPin);
brightness = (1023 - sensorValue) / 1023 * 255; // Gjør om fra 4-bit verdi til RGB-verdi
                                                // Jo høyere sensorverdi, jo lavere lysverdi
analogWrite(ledPin, brightness);
delay(250);
}
