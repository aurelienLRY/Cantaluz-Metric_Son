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

// Phases de la respiration guidée (mode Méditation)
enum MedPhase : uint8_t {
  MED_IDLE = 0,
  MED_COUNTDOWN,
  MED_INSPIRE,
  MED_HOLD,        // Retiens (poumons pleins, après inspire)
  MED_EXPIRE,
  MED_HOLD_EMPTY,  // Air bloqué (poumons vides, après expire)
  MED_PAUSE,
  MED_DONE
};

// Phases du Défi Fifou (jeu du calme)
enum FifouPhase : uint8_t {
  FIFOU_IDLE = 0,
  FIFOU_COUNTDOWN,
  FIFOU_PLAYING,
  FIFOU_WON,
  FIFOU_LOST,
  FIFOU_DONE
};

// État d'une partie Défi Fifou (API web + ModeDefiFifou.cpp)
struct DefiFifouState {
  uint8_t durProfile;           // 0 = 2 min, 1 = 5 min, 2 = 10 min
  uint32_t sessionDurMs;
  FifouPhase phase;
  bool countdownActive;
  bool sessionActive;
  bool endAnimActive;
  unsigned long countdownStartMs;
  unsigned long sessionStartMs;
  unsigned long endAnimStartMs;
  float litLeds;                // Nombre de LED allumées (fractionnaire)
  float gainRatePerSec;         // Vitesse en zone calme (LED/s)
  float lossRatePerSec;         // Vitesse en zone rouge (LED/s, plus lente)
};

// État d'une séance Méditation guidée (API web + ModeMeditation.cpp)
struct MeditationState {
  uint8_t durProfile;           // 0 = 2 min, 1 = 5 min, 2 = 10 min
  uint32_t sessionDurMs;        // Durée totale choisie (ms)
  MedPhase phase;
  bool countdownActive;
  bool sessionActive;
  unsigned long countdownStartMs;
  unsigned long sessionStartMs;
  unsigned long phaseStartMs;
  unsigned long nextLedStepMs;
  int cycleLedIndex;            // Prochaine LED à allumer (0 .. LED_COUNT)
  int phaseEndLed;              // Fin de segment pour la phase courante
  uint16_t msPerLed;            // Délai entre deux LED dans la phase courante
};

// Réglages modifiables en live (Config.h au boot, puis page web /api/settings)
struct LiveConfig {
  uint8_t activeMode;     // MODE_IMMEDIAT, MODE_LENT, MODE_MEDITATION ou MODE_DEFI_FIFOU (app web)
  int adcFinZoneVert;     // Seuil fin zone verte (peak ADC)
  int adcFinZoneOrange;   // Seuil fin zone orange (peak ADC)
  uint8_t maxBrightness;  // Luminosité ruban 0-255
  uint8_t attackPercent;  // Vitesse montée barre VU (%)
  uint8_t sensitivity;  // Sensibilité micro 0-100 (app Réglages)
};

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

  LiveConfig live;               // Réglages temps réel (web + Config.h au démarrage)
  RuntimeConfig run;             // Paramètres convertis (voir ci-dessus)
  MeditationState med;           // Séance Méditation guidée
  DefiFifouState fifou;          // Partie Défi Fifou

  int lastPeak;                  // Dernier peak micro (pour API web)
  int lastMicAvg;                // Dernière moyenne micro (pour API web)

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

  int micGate;                       // Porte bruit (depuis sensibilité)
  int micSpan;                       // Peak effectif pour barre à 100 %
  int micDeadband;                   // Zone morte barre VU
};

extern AppState g;  // Instance unique — toute la mémoire « vivante » du projet

// Permet d'afficher VERT / ORANGE / ROUGE dans le moniteur série
const char *stateName(ColorState s);

// Permet de remplir g.live depuis Config.h selon MODE_ACTIF (appeler avant init LED)
void liveConfigInit();

// Permet de recalculer g.run.* depuis les #define de Config.h — mode immédiat (appeler au boot)
void configApply();

// Permet de recalculer g.run.* depuis la section MODE LENT de Config.h
void configApplyLent();

// Permet d'appliquer attackPercent → g.run.attackRate après changement web
void liveApplyAttackRate();

// Permet de restaurer tous les réglages par défaut (Config.h, garde le mode actuel)
void liveConfigResetDefaults();

// Permet de restaurer un seul réglage : "vert", "orange", "bright", "attack", "sens"
void liveResetField(const char *field);
