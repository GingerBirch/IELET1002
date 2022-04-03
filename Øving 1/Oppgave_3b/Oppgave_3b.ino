#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "";
const char* password = "";

WebServer server(80);

const int potPin = 34;
const int fotoResPin = 32;

unsigned long previousMillis = 0;

//funksjon som lager nettsiden
String refreshWebData() {
  float sensorDataArr[2];
  sensorDataArr[0] = analogRead(potPin) * 3.3 / 1023;
  sensorDataArr[1] = analogRead(fotoResPin) * 3.3 / 1023;

  Serial.println(sensorDataArr[0]);
  Serial.println(sensorDataArr[1]);

  String HTMLdata = "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "<title>Sensordata</title>"
  "<meta http-equiv='refresh' content='0.5'>"
  "</head>"
  "<body>"
  "<hl>Sensordata:</hl>"
  "</body>"
  "</html>";

  HTMLdata += "<h2>Potmeter: ";
  HTMLdata += sensorDataArr[0];
  HTMLdata += "V";
  HTMLdata += "</h2>";
  
  HTMLdata += "<h2>Fotoresistor: ";
  HTMLdata += sensorDataArr[1];
  HTMLdata += "V";
  HTMLdata += "</h2>";

  return HTMLdata;
}

void handle_root() {
  server.send(200, "text/html", refreshWebData());
}

void setup() {
  Serial.begin(9600);

  analogReadResolution(10);

  pinMode(potPin, INPUT);
  pinMode(fotoResPin, INPUT);

  //printer informasjon om oppkobling i serial monitor
  Serial.println("Try connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  //printer informasjon om serveren i serial monitor
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);

  //starter serverprosessen
  server.begin();
  Serial.println("HTTP server started");
  delay(5000);
}

void loop() {
  //holder serveren oppe og går
  server.handleClient();

  unsigned long currentMillis = millis();

  //refresher nettsiden og sender nye data hvert halve sekund
  if (currentMillis - previousMillis >= 500) {
    previousMillis = currentMillis;
    server.send(200, "text/html", refreshWebData());
  }
}
