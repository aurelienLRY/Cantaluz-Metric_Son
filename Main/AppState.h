#pragma once
/*
 * AppState.h — Mémoire globale du programme (variable g)
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Centralise tout ce qui change en cours d'exécution :
 *   - tableau des couleurs LED,
 *   - niveau de la barre VU,
 *   - état vert/orange/rouge,
 *   - minuteurs anti-rebond des flashs.
 *
 * Où modifier quoi ?
 * --------------------
 *   - Réglages fixes        → Config.h puis configApply()
 *   - Pas besoin de toucher aux champs ici en usage normal.
 *
 * Accès : partout via  extern AppState g;  (défini dans AppState.cpp)
 */

#include <FastLED.h>
#include "Config.h"
#include "Types.h"

// Valeurs calculées depuis Config.h (% et secondes) — remplies par configApply()
struct RuntimeConfig {
  float attackRate;              // Vitesse montée barre (ex. 0.45 si ATTACK_PERCENT=45)
  float avgSmooth;               // Lissage moyenne peak
  float peakSmoothFactor;        // Lissage peak pour flashs
  unsigned long descentDelayMs;  // Délai avant descente barre (ms)
  float descentRate;             // Vitesse descente barre (niveau / seconde)
  unsigned long transitionCooldownMs; // Entre deux séries de flashs bleus (ms)
  uint8_t bootStepMs;            // Délai animation VU au boot
};

// État vivant du sketch — une seule instance globale g
struct AppState {
  CRGB leds[LED_COUNT];          // Couleurs de chaque LED (buffer FastLED)

  RuntimeConfig run;             // Paramètres convertis (voir ci-dessus)

  int ledFinZoneVert;            // Index LED : dernière LED de la zone verte
  int ledFinZoneOrange;          // Index LED : dernière LED de la zone orange
  int vuMaxPeak;                 // Peak ADC pour barre VU à 100 %

  int threshOrangeUp;            // Seuil montée → orange (flash)
  int threshRedUp;               // Seuil montée → rouge (flash)
  int threshGreenDn;             // Seuil descente avec hystérésis → vert
  int threshOrangeDn;            // Seuil descente avec hystérésis → orange

  float displayLevel;            // Hauteur barre affichée 0.0-1.0
  float peakAverage;             // Moyenne glissante du peak
  float peakSmooth;              // Peak lissé pour décisions flash

  ColorState currentState;       // Palier actuel après flash (vert/orange/rouge)
  ColorState pendingState;       // Palier cible pendant les flashs bleus
  ColorState holdTarget;         // Palier en attente de validation (anti-rebond)

  bool transitionActive;         // true pendant la série de flashs bleus
  uint8_t flashStep;             // Étape courante dans l'animation flash

  unsigned long belowAvgSinceMs;     // Début période « sous la moyenne » (descente barre)
  unsigned long stateHoldSinceMs;      // Début maintien au-dessus du seuil (avant flash)
  unsigned long lastTransitionEndMs;   // Fin du dernier flash (cooldown)
  unsigned long lastFlashMs;           // Horodatage impulsion flash en cours
  unsigned long lastLoopMs;            // Horodatage boucle (calcul dt)
  unsigned long lastDebugMs;           // Horodatage dernier log série
  unsigned long belowZoneSinceMs;      // Anti reset timer sur micro-coupure sous seuil
};

extern AppState g;  // Instance unique — toute la mémoire « vivante » du projet

// Permet d'afficher VERT / ORANGE / ROUGE dans le moniteur série
const char *stateName(ColorState s);

// Permet de recalculer g.run.* depuis les #define de Config.h — mode immédiat (appeler au boot)
void configApply();

// Permet de recalculer g.run.* depuis la section MODE LENT de Config.h
void configApplyLent();
