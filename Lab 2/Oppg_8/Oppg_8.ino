#include <Servo.h>

const uint8_t EN1 = 11;
const uint8_t IN1 = 13;
const uint8_t IN2 = 12;
const int potPin = A0;
const int tiltPin = 7;
const int servoPin = 9;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(tiltPin, INPUT);
  //pinMode(servoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(potPin);
  int tiltVal = digitalRead(tiltPin);
  float rpm = map(potVal, 0, 511, -250, 250);
  int servoValNeg = map(potVal, 0, 255, 0, -180);
  int servoValPos = map(potVal, 256, 1023, 180, 0);
  Serial.println(potVal);
  
  if (rpm > 0 && tiltVal == HIGH){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN1, rpm);
    servo.write(servoValPos);
    //Serial.println(servoValPos);
  }
  else if (rpm < 0 && tiltVal == HIGH){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, abs(rpm));
    servo.write(abs(servoValNeg));
    //Serial.println(servoValNeg);
  }
  else{
    analogWrite(EN1, 0);
  }
}
