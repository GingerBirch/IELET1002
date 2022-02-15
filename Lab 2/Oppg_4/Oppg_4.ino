const uint8_t EN1 = 11;
const uint8_t IN1 = 13;
const uint8_t IN2 = 12;
const int potPin = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(potPin);
  float rpm = map(potVal, 0, 1023, -250, 250);
  Serial.println(rpm);

  if (rpm > 50){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, rpm);
  }
  else if (rpm < -50){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, abs(rpm));
  }
  else{
    analogWrite(EN1, 0);
  }
}
