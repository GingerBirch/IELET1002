int randomNumber;
int amount[6]; // Liste for de tilfeldige tallene
const int buttonPin = 2;
int buttonState = 0;
int buttonPressed = LOW;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(buttonPin, INPUT);  
}

void loop() {
  buttonPressed = digitalRead(buttonPin);
  if (buttonPressed == HIGH){
    buttonState++;
  }

  switch (buttonState){
    case 0:
    Serial.println("Trykk på knappen for å generere tallene.");
    Serial.println(""); // Legger til mellomrom
    buttonState++; // Legger til en hviletilstand
    break;
    
    case 2:
    delay(200); // Liten delay for å ikke få feilmelding ved forrige trykk
    for (int i = 0; i < 10000; i++){ // Fyller opp lista med tall
      randomNumber = random(1, 7); // Tilfeldig tall fra og med 1 til og med 6
      amount[randomNumber - 1]++; // Det tilfeldige tallet registreres på rett indeksplass
      if (digitalRead(buttonPin)){ // Hvis knappen blir trykt før lista med tall er full
        buttonState = 404;
      }
    }
    if (buttonState == 2){ // Hvis knappen ikke har blitt trykt mens lista fyltes opp
      Serial.println("Trykk på knappen for å skrive rapporten.");
      Serial.println("");
      buttonState++; // Legger til en hviletilstand
    }
    break;

    case 4:
    for (int j = 0; j < 6; j++){ // Rapporten printes
      Serial.print("Tallet ");
      Serial.print(j + 1);
      Serial.print(" ble generert ");
      Serial.print(amount[j]);
      Serial.print(" ganger og det tilsvarer ");
      Serial.print(float(amount[j]) * 100 / 10000);
      Serial.println(" prosent.");
    }
    Serial.println("");
    for (int k = 0; k < 6; k++){ // Tømmer lista for innhold
      amount[k] = 0;
    }
    buttonState = 0;
    delay(5000); // delay før ny generering av tall
    break;

    case 404: // Feilmelding
    Serial.println("No data available yet.");
    Serial.println("");
    buttonState = 0;
    for (int k = 0; k < 6; k++){ // Tømmer lista for innhold
      amount[k] = 0;
    }
    break;
  }
}
