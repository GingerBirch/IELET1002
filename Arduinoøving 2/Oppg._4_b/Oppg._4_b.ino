int randomNumber;
const int interval = 1000; // Hvor ofte random nummer skal genereres
unsigned long previousMilli = 0;
unsigned long currentMilli;
const int buzzPin = 8;
int frequenzy = 1000;
int buzzLenght = 200;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  currentMilli = millis();
  // Hvis differansen mellom nåværende tall og forrige lagrede tall er 1000
  if (currentMilli - previousMilli == interval){
    randomNumber = random(1, 7); // Tilfeldig tall mellom 1 og 6 genereres
    Serial.println(randomNumber);
    previousMilli = currentMilli;
    if (randomNumber == 6){
      tone(buzzPin, frequenzy, buzzLenght);
    }
  }
  
}
