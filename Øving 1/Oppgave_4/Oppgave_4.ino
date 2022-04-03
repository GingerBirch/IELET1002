const int LED = 12;
const int buzzer = 14;
const int channelLED = 0;
const int channelBuzzer = 1;
int brightness = 0; // Variabel for lysverdien
int count = 15; // Hvor mye lysverdien endres hvert steg
int increase = true;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  ledcSetup(channelLED, 1000, 8);
  ledcAttachPin(LED, channelLED);
  ledcSetup(channelBuzzer, 1000, 8);
  ledcAttachPin(buzzer, channelBuzzer);
}

//liste med forskjellige frekvenser
int buzzerFreq[] = {200, 300, 400, 500, 600, 700, 800, 900};

void pulserendeLED() {
  // Øker lysverdien jevnt opp til maksverdi
  while (increase == true){
    ledcWrite(channelLED, brightness);
    brightness = brightness + count;
    if (brightness == 255){ // Ved maks lysverdi
      increase = false;
    }
    delay(100);
  }
  // Senker lysverdien jevnt ned til minimalverdi
  while (increase == false){
    ledcWrite(channelLED, brightness);
    brightness = brightness - count;
    if (brightness == 0){ // Ved minimal lysverdi
      increase = true;
    }
    delay(100);
  }
}

void loop(){
  pulserendeLED();
  //spiller av en tilfelig frekvens
  int randomFreq = random(8);
  ledcWriteTone(channelBuzzer, buzzerFreq[randomFreq]);
}
