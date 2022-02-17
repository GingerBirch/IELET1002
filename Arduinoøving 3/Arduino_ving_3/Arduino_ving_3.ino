const int redLED = 10;  //RGB-rød
const int greenLED = 9; //RGB-grønn

const int LED1 = 6;       //Spiller 1 - LED
const int LED2 = 7;       //Spiller 2 - LED
const int player1 = 3;    //Spiller 1 - knapp
const int player2 = 4;    //Spiller 2 - knapp
const int buzzerPin = 11; //Piezo

int winner;               //Initialiserer vinnerindikatoren
int looser;               //Initialiserer feilindikatoren

unsigned long wait = 0;
unsigned long now = 0;

// Liste med vinnermelodi
int winnerMelody[] = {
  750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400, 1450, 1500, 1550, 1600, 1650, 1700
};

// Liste med tapermelodi
int looserMelody[] = {
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200
};

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(player1, INPUT);
  pinMode(player2, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Setter ledlysene til standardtilstander
  digitalWrite(redLED, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  looser = 0;
  now = millis(); // Variabel som teller millisekunder
  wait = now + random(3000, 6000); // Legger til en tid mellom 3 og 6 sekunder, som er "startskuddet"

  // Løkke som kjører så lenge "startskuddet" ikke er nådd og ingen spillere har trykker på knappen
  while (millis() < wait && digitalRead(player1) == HIGH && digitalRead(player2) == HIGH){
  }
  // Hvis en spiller trykker på knappen før "startskuddet"
  if (digitalRead(player1) == LOW){
    looser = LED1;
  }
  if (digitalRead(player2) == LOW){
    looser = LED2;
  }
  digitalWrite(redLED, LOW);

  // Hvis ingen trykket på knappen før "startskuddet"
  if (looser == 0){
    digitalWrite(greenLED, HIGH);
    // Løkke som kjører så lenge ingen har trykket på knappen
    while (digitalRead(player1) == HIGH && digitalRead(player2) == HIGH){
    }
    // Når en spiller trykker på knappen. Førstemann til mølla
    if (digitalRead(player1) == LOW){
      winner = LED1;
    }
    if (digitalRead(player2) == LOW){
      winner = LED2;
    }
    
    // Vinnersekvens
    for (int note = 0; note < 20; note++){
      // Spiller av en og en pitch i vinnermelodien
      tone(buzzerPin, winnerMelody[note], 100);

      // Ledlysene blinker
      digitalWrite(greenLED, HIGH);
      digitalWrite(winner, LOW);
      delay(50);
      digitalWrite(winner, HIGH);
      digitalWrite(greenLED, LOW);
      delay(50);
    }
  }

  // Hvis noen trykket på knappen før "startskuddet"
  else{
    // Tapersekvens
    for (int note = 0; note < 20; note++){
      // Spiller av en og en pitch i tapermelodien
      tone(buzzerPin, looserMelody[note], 100);

      // Ledlysene blinker
      digitalWrite(redLED, HIGH);
      digitalWrite(looser, LOW);
      delay(50);
      digitalWrite(looser, HIGH);
      digitalWrite(redLED, LOW);
      delay(50);
    }
  }
}
