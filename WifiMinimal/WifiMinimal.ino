/*
 * WifiMinimal.ino — TEST MATÉRIEL Wi-Fi seul (WeMos D1 mini / ESP8266)
 *
 * Si ce sketch ne montre pas le réseau "Cantaluz_TEST", le problème
 * est la carte, l'alimentation ou les réglages Arduino IDE — pas Cantaluz.
 *
 * IDE : Carte = LOLIN(WEMOS) D1 R1 (ou D1 R2 & mini selon votre carte)
 *       Outils → Effacer la flash : « All Flash Contents » (1 fois)
 * Moniteur série : 115200
 */

#include <ESP8266WiFi.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  delay(1500);
  Serial.println();
  Serial.println(F("=== Test WiFi minimal ESP8266 ==="));
  Serial.print(F("Heap libre: "));
  Serial.println(ESP.getFreeHeap());

  WiFi.persistent(false);
  WiFi.disconnect(true);
  WiFi.softAPdisconnect(true);
  delay(100);

  WiFi.forceSleepWake();
  WiFi.mode(WIFI_AP);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.setOutputPower(20.5f);

  IPAddress ip(192, 168, 4, 1);
  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));

  const char *ssid = "Cantaluz_TEST";
  const char *pass = "12345678";
  bool ok = WiFi.softAP(ssid, pass, 1, 0, 4);
  delay(800);

  Serial.print(F("softAP: "));
  Serial.println(ok ? F("OK") : F("ECHEC"));
  Serial.print(F("SSID visible: "));
  Serial.println(ssid);
  Serial.print(F("Mot de passe: "));
  Serial.println(pass);
  Serial.print(F("IP: "));
  Serial.println(WiFi.softAPIP());

  if (ok) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    while (true) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
    }
  }
}

void loop() {
  static unsigned long last = 0;
  if (millis() - last > 3000) {
    last = millis();
    Serial.print(F("Stations connectees: "));
    Serial.println(WiFi.softAPgetStationNum());
  }
  yield();
}
