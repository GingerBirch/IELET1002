int randomNumber;
int amount[6]; // Liste for de tilfeldige tallene

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  for (int i = 0; i < 10000; i++){ // Fyller opp lista med tall
    randomNumber = random(1, 7);
    amount[randomNumber - 1]++;
  }
  for (int j = 0; j < 6; j++){ // Rapporten printes
    Serial.print("Tallet ");
    Serial.print(j + 1);
    Serial.print(" ble generert ");
    Serial.print(amount[j]);
    Serial.print(" ganger og det tilsvarer ");
    Serial.print(float(amount[j]) * 100 / 10000);
    Serial.println(" prosent.");
  }
  for (int k = 0; k < 6; k++){ // Tømmer lista for innhold
    amount[k] = 0;
  }
  Serial.println(""); // Legger til mellomrom mellom rapportene
  delay(5000);
}
