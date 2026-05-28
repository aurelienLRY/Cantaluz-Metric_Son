/*
 * Main.ino — Point d'entrée Arduino Cantaluz (WeMos D1 / ESP8266)
 *
 * Matériel :
 *   - Micro MAX4466 sur A0
 *   - Ruban WS2812B sur D2 (GPIO4), alim 5 V externe, GND commun
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Très court : initialise les broches, le port série (debug), puis délègue
 * tout le travail à Modes.cpp selon MODE_ACTIF dans Config.h.
 *
 * Fichiers du projet (ordre logique) :
 *   Config.h         → VOS réglages (% , secondes, seuils ADC)
 *   Types.h          → noms des états et structures de données
 *   Convert.h        → conversion % / secondes
 *   AppState.*       → mémoire globale g
 *   MicSensor.*      → lecture micro + hauteur barre
 *   LedStrip.*       → ruban et couleurs par zone
 *   FlashEtat.*      → flashs bleus montée de palier
 *   ModeImmediat.*   → mode « immédiat »
 *   ModeLent.*       → mode « lent » (dòç)
 *   Modes.*          → choix du mode
 *   DebugLog.*       → traces série
 *
 * Documentation détaillée : FICHIERS.md
 */

#include "Config.h"
#include "Modes.h"

void setup() {
  pinMode(MIC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

#ifdef DEBUG_SERIAL
  Serial.begin(SERIAL_BAUD);
  delay(300);
  Serial.println(F("=== Cantaluz ==="));
#if MODE_ACTIF == MODE_LENT
  Serial.println(F("Mode: LENT (dòç)"));
#elif MODE_ACTIF == MODE_IMMEDIAT
  Serial.println(F("Mode: IMMEDIAT"));
#else
  Serial.println(F("Mode: (inconnu)"));
#endif
#endif

  modesSetup();
}

void loop() {
  modesLoop();
}
