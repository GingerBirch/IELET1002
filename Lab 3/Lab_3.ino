const int redLED = 10;  //RGB-rød
const int greenLED = 9; //RGB-grønn
const int blueLED = 8;  //RGB-blå

const int LED1 = 6;       //Spiller 1 - LED
const int LED2 = 7;       //Spiller 2 - LED
const int player1 = 3;    //Spiller 1 - knapp
const int player2 = 4;    //Spiller 2 - knapp
const int buzzerPin = 11; //Piezo

int winner;               //Vinnerindikatoren
int gameWinner;           //Spillvinnerindikatoren
int looser;               //Taperindikatoren
int gameLooser;           //Spilltaperindikatoren
int gameMode = 0;         //Spillmodus
int player1points;        //Spillpoeng - spiller 1
int player1score = 0;     //Total poengsum - spiller 1
int player2points;        //Spillpoeng - spiller 2
int player2score = 0;     //Total poengsum - spiller 2
int margin;               //Poengforskjell
int blueChance;           //Sjansen for blått lys
int points;               //Poeng tjent ved grønn RGB

unsigned long waitRed = 0;      //Hvor lenge RGB skal lyse rødt
unsigned long waitBlue = 0;     //Hvor lenge RGB skal lyse blått
unsigned long startGreen = 0;   //Starttiden for når RGB skifter til grønt
unsigned long timePressed = 0;  //Registrert tid når knapp trykkkes mens RGB er grønt

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
  pinMode(blueLED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(player1, INPUT);
  pinMode(player2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

// Funksjon som printer informasjon om spillet til seriemonitor
int gameInfo(){
  Serial.println("Reaksjonsspill!! Førstemann til å trykke på knappen når lyset blir grønt! ");
  Serial.println("Hvis du trykker mens lyset er rødt mister du poeng! Trykker du når lyset blir blått mister du enda mere poeng!");
  Serial.println("Skriv 's' i serial monitor for å starte spill");
  Serial.println("Skriv 'q' i serial monitor for å avslutte spill og vise poengscore");
  Serial.println("Skriv 'r' i serial monitor for å resette poengsum");
}

// Funksjon som lar deg velge mellom å spille, printe siste resultat eller resette poengsum fra seriemonitor
int gameMenu(){
  int incomingByte;
  if (Serial.available() > 0){ // Hvis det er ledige bytes som kan lese informasjon
    incomingByte = Serial.read();
  }
  if (incomingByte == 's'){
    gameMode = 2;
  }
  if (incomingByte == 'q'){
    gameMode = 3;
  }
  if (incomingByte == 'r'){
    gameMode = 4;
  }
}

// Funksjon for selve spillet
int game(){
  // Opptjente poeng dette spillet startet på null
  player1points = 0;
  player2points = 0;
  // Løkke som kjører så lenge ingen av spillerne har oppnådd minst 50 poeng
  while (player1points < 50 && player2points < 50){
    gameSetup();
    redLight();
    blueChance = random(11);
    if (blueChance < 4){ // 30% sjanse for at RGB blir blå
      blueLight();
    }
    greenLight();
    Serial.print("Poeng spiller 1: ");
    Serial.print(player1points);
    Serial.print("      Poeng spiller 2: ");
    Serial.println(player2points);
  }
  // Lagrer vinner og taper
  if (player1points == 50){
    gameWinner = 1;
    gameLooser = 2;
  }
  else{
    gameWinner = 2;
    gameLooser = 1;
  }
  // Funksjon som lagrer opptjente poeng
  scoreManager();
}

// Funksjon for standardtilstandene
int gameSetup(){
  digitalWrite(redLED, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  looser = 0;
}

// Funksjon for første del av en spillrunde, når RGB er rød
int redLight(){
  // Legger til en tid mellom 3 og 6 sekunder, som er hvor lenge RGB er rød
  waitRed = millis() + random(3000, 6000);
  // while-løkke som kjører så lenge RGB er rød og ingen spillere har trykket på knappen
  while (millis() < waitRed && digitalRead(player1) == HIGH && digitalRead(player2) == HIGH){
  }
  // Hvis en spiller trykker på knappen mens RGB er rød
  if (digitalRead(player1) == LOW){
    looser = LED1;
    player1points--;
  }
  if (digitalRead(player2) == LOW){
    looser = LED2;
    player2points--;
  }
  digitalWrite(redLED, LOW);
}

// Funksjon for eventuell mellomdel av en spillrunde, når RGB er blå
int blueLight(){
  // Hvis ingen trykket på knappen mens RGB var rød
  if (looser == 0){
    digitalWrite(blueLED, HIGH);
    // Legger til en tid mellom 1.5 og 4 sekunder, som er hvor lenge RGB er blå
    waitBlue = millis() + random(1500, 4000);
    // while-løkke som kjører så lenge RGB er blå og ingen spillere har trykket på knappen
    while (millis() < waitBlue && digitalRead(player1) == HIGH && digitalRead(player2) == HIGH){
    }
    // Hvis en spiller trykker på knappen mens RGB er blå
    if (digitalRead(player1) == LOW){
      looser = LED1;
      player1points -= 5;
    }
    if (digitalRead(player2) == LOW){
      looser = LED2;
      player2points -= 5;
    }
    digitalWrite(blueLED, LOW);
  }
}

// Funksjon for siste del av en spillrunde, når RGB er grønn
int greenLight(){
  if (looser == 0){  // Hvis ingen trykket på knappen mens RGB var rød eller blå
    digitalWrite(greenLED, HIGH);
    startGreen = millis(); // Registrerer tiden når RGB blir grønn
    // Løkke som kjører så lenge ingen har trykket på knappen
    while (digitalRead(player1) == HIGH && digitalRead(player2) == HIGH){
    }
    // Når en spiller trykker på knappen
    if (digitalRead(player1) == LOW){
      winner = LED1;
      player1points += pointsManager();
    }
    if (digitalRead(player2) == LOW){
      winner = LED2;
      player2points += pointsManager();
    }
    // Kjører vinnersekvensen
    winnerSequence();
  }
  else{  // Hvis noen trykket på knappen mens RGB var rød eller blå
    // Kjører tapersekvensen
    looserSequence();
  }
}

// Funksjon som regner ut hvor mange poeng en spiller får når den trykker på knappen mens RGB er grønn
int pointsManager(){
  timePressed = millis() - startGreen; // Regner ut tiden fra RGB ble grønn til knappetrykk
  // Hvis spiller trykker på knappen før det har gått 200 millisekunder
  if (timePressed < 200){
    // Spiller får 10 poeng
    points = 10;
  }
  // Hvis spiller trykker på knappen etter det har gått 200 millisekunder og før det har gått 500 millisekunder
  else if ( timePressed >= 200 && timePressed < 500){
    // Spiller får 5 poeng
    points = 5;
  }
  // Hvis spiller trykker på knappen etter det har gått 500 millisekunder
  else{
    // Spiller får 1 poeng
    points = 1;
  }
  return points; // Returnerer antall poeng
}

// Funksjon som kjører vinnersekvens
int winnerSequence(){
  // for-løkke som kjører 20 ganger, vinnersekvens blir da på 2 sekunder
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
  digitalWrite(winner, LOW);
}

// Funksjon som kjører tapersekvens
int looserSequence(){
  // for-løkke som kjører 20 ganger, tapersekvens blir da på 2 sekunder
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
  digitalWrite(looser, LOW);
}

// Funksjon som lagrer opptjente poeng
int scoreManager(){
  player1score += player1points;
  player2score += player2points;
  margin = abs(player1points-player2points);
}

// Funksjon som printer siste vinner og med hvor mange poeng den vant med
int gameQuit(){
  // Hvis ingen har noen poeng ennå
  if (player1score == 0 && player2score == 0){
    Serial.println("Ingen har fått noen poeng ennå.");
  }
  // Hvis spiller 1 er vinner
  else if (gameWinner == 1){
    Serial.print("Spiller 1 vant med ");
    Serial.print(margin);
    Serial.println(" poeng.");
  }
  // Hvis spiller 2 er vinner
  else if (gameWinner == 2){
    Serial.print("Spiller 2 vant med ");
    Serial.print(margin);
    Serial.println(" poeng.");
  }
  delay(1); // Legger til en ørliten delay for at funksjonen bare skal kjøres en gang
}

// Funksjon som nullstiller total poengsum
int gameReset(){
  player1score = 0;
  player2score = 0;
}

void loop() {
  // switch...case som inneholder hovedfunksjonene
  switch(gameMode){
    case 0:
    gameInfo();
    gameMode = 1;
    break;
    
    case 1:
    gameMenu();
    break;

    case 2:
    game();
    gameMode = 1;
    break;

    case 3:
    gameQuit();
    gameMode = 1;
    break;

    case 4:
    gameReset();
    gameMode = 1;
    break;
  }
}
