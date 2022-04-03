uint8_t LED = 22; //kobler LED til digtalpinne 22

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  //LED blinker med et intervall på 500ms
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
