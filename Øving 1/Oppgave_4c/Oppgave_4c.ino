const int servo = 22;
const int channelServo = 2;
int angle = 90; //starter servo midt på
int increase = true;

void setup() {
  pinMode(servo, OUTPUT);
  ledcSetup(channelServo, 1000, 8);
  ledcAttachPin(servo, channelServo);
}

void roterendeServo() {
  // Øker lysverdien jevnt opp til maksverdi
  while (increase == true){
    ledcWrite(channelServo, angle);
    angle++;
    if (angle == 180){ // Ved maks lysverdi
      increase = false;
    }
    delay(100);
  }
  // Senker lysverdien jevnt ned til minimalverdi
  while (increase == false){
    ledcWrite(channelServo, angle);
    angle--;
    if (angle == 0){ // Ved minimal lysverdi
      increase = true;
    }
    delay(100);
  }
}

void loop() {
  ledcWrite(channelServo, 1);
}
