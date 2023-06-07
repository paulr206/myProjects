#include <ESP8266WiFi.h>

// char* ssid = "FRITZ!Box 7530 JR";
// char* password =  "42424968210568278054";
const char *ssid = "OnePlus 9";    // ssid Marvin
const char *password = "z3ehhs97"; // Passwort WLAN

const uint16_t port = 5000;
char *host = "192.168.166.166";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;

  if (!client.connect(host, port)) {

    Serial.println("Connection to host failed");

    delay(1000);
    return;
  }

  Serial.println("Connected to server successful!");

  client.print("Hello from ESP32!");

  Serial.println("Disconnecting...");
  client.stop();

  delay(10000);
}
