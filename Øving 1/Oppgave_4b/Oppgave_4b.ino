const int buzzer = 14;
const int channelBuzzer = 1;

void setup() {
  pinMode(buzzer, OUTPUT);
  ledcSetup(channelBuzzer, 1000, 8);
  ledcAttachPin(buzzer, channelBuzzer);
}

//liste med forskjellige frekvenser
int buzzerFreq[] = {200, 300, 400, 500, 600, 700, 800, 900};

void loop() {
  //spiller av en tilfeldig frekvens
  int randomFreq = random(8);
  ledcWriteTone(channelBuzzer, buzzerFreq[randomFreq]);
  delay(100);
}
