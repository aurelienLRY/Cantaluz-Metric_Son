/*
 * Main.ino — Point d'entrée Arduino Cantaluz (ESP32-WROOM-32U)
 *
 * Matériel :
 *   - Micro MAX4466 sur GPIO34 (ADC1), alim 3,3 V
 *   - Ruban WS2812B sur GPIO4, alim 5 V externe, GND commun
 *   - Antenne U.FL branchée (obligatoire pour le Wi-Fi)
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Très court : initialise l'ADC, les broches, le port série (debug), puis délègue
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
 *   WifiPortal.*     → réseau Cantaluz + page web (téléphone)
 *
 * Wi-Fi (Config.h) : réseau Cantaluz → http://cantaluz.local
 * (portail captif : la page peut s'ouvrir toute seule à la connexion)
 *
 * Documentation détaillée : FICHIERS.md
 */

#include "Config.h"
#include "Modes.h"
#include "WifiPortal.h"

void setup() {
#ifdef DEBUG_SERIAL
  Serial.begin(SERIAL_BAUD);
  delay(1000);
#endif

  // ADC 10 bits (0–1023) pour rester aligné avec les seuils de Config.h
  analogReadResolution(10);
  analogSetPinAttenuation(MIC_PIN, ADC_11db);

  pinMode(MIC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

#ifdef DEBUG_SERIAL
  Serial.println(F("=== Cantaluz (ESP32) ==="));
#if MODE_ACTIF == MODE_LENT
  Serial.println(F("Mode: LENT (Standard)"));
#elif MODE_ACTIF == MODE_MEDITATION
  Serial.println(F("Mode: MEDITATION GUIDEE"));
#elif MODE_ACTIF == MODE_DEFI_FIFOU
  Serial.println(F("Mode: DEFI FIFOU"));
#elif MODE_ACTIF == MODE_IMMEDIAT
  Serial.println(F("Mode: IMMEDIAT"));
#else
  Serial.println(F("Mode: (inconnu)"));
#endif
#endif

  modesSetup();

#if WIFI_ENABLE
#ifdef DEBUG_SERIAL
  Serial.println(F("Demarrage WiFi (apres init ruban)..."));
#endif
  wifiPortalStartRadio();
  wifiPortalStartWeb();
#endif
}

void loop() {
  modesLoop();
}
