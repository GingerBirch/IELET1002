const uint8_t EN1 = 11;
const uint8_t IN1 = 13;
const uint8_t IN2 = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  for (uint8_t i = 50; i < 155; i++){
    analogWrite(EN1, i);
    delay(100);
  }
  for (uint8_t i = 155; i > 50; i--){
    analogWrite(EN1, i);
    delay(100);
  }
}
