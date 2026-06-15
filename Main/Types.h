#pragma once
/*
 * Types.h — Définitions de types partagés (PAS des réglages utilisateur)
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Il décrit les « formes » de données utilisées dans tout le projet :
 *   - les 3 paliers sonores (vert / orange / rouge),
 *   - le contenu d’une mesure micro,
 *   - la liste des modes LED vs bruit (pour plus tard).
 *
 * Où modifier quoi ?
 * --------------------
 *   - Réglages (seuils, délais, nombre de LED…)  →  Config.h
 *   - Comportement du programme                  →  ModeImmediat.cpp, LedStrip.cpp, etc.
 *   - Ajouter un nouveau mode plus tard          →  BruitLedMode ci-dessous + Modes.cpp
 *
 * En général, vous n’avez PAS besoin de toucher à Types.h pour faire tourner le sketch.
 */

#include <stdint.h>

// ═══════════════════════════════════════════════════════════════
//  ColorState — Palier sonore (états vert / orange / rouge)
// ═══════════════════════════════════════════════════════════════
/*
 * Représente dans quelle « zone » se trouve le son par rapport aux plages ADC
 * définies dans Config.h (ADC_FIN_ZONE_VERT, ADC_FIN_ZONE_ORANGE).
 *
 * Utilisé pour :
 *   - savoir quand déclencher un flash bleu (montée vert → orange → rouge),
 *   - mémoriser l’état courant (currentState dans AppState),
 *   - afficher les noms dans le moniteur série (stateName).
 *
 * Correspondance avec le ruban :
 *   STATE_GREEN  → début du ruban, couleur verte
 *   STATE_ORANGE → milieu, couleur orange
 *   STATE_RED    → fin du ruban, couleur rouge
 *
 * Ne pas renommer les valeurs 0, 1, 2 : le code fait STATE + 1 pour monter d’un cran.
 */
enum ColorState : uint8_t {
  STATE_GREEN  = 0,  // Zone calme / faible (peak ≤ ADC_FIN_ZONE_VERT)
  STATE_ORANGE = 1,  // Zone moyenne (peak entre vert et orange)
  STATE_RED    = 2   // Zone forte (peak > ADC_FIN_ZONE_ORANGE)
};

// ═══════════════════════════════════════════════════════════════
//  BruitLedMode — Liste des modes « LED vs bruit » (extensible)
// ═══════════════════════════════════════════════════════════════
/*
 * Chaque mode = une façon différente de réagir au micro et d’animer le ruban.
 * Le mode actif est choisi dans Config.h avec MODE_ACTIF (pas ici).
 *
 * Modes disponibles :
 *   BRUIT_MODE_IMMEDIAT → VU réactif + flash bleu (ModeImmediat.cpp)
 *   BRUIT_MODE_LENT     → VU adouci, sans flash (ModeLent.cpp)
 *   BRUIT_MODE_MEDITATION → respiration guidée (ModeMeditation.cpp)
 *   BRUIT_MODE_DEFI_FIFOU → jeu du calme (ModeDefiFifou.cpp)
 */
enum BruitLedMode : uint8_t {
  BRUIT_MODE_IMMEDIAT = 0,
  BRUIT_MODE_LENT     = 1,
  BRUIT_MODE_MEDITATION = 2,
  BRUIT_MODE_DEFI_FIFOU = 3
};

// ═══════════════════════════════════════════════════════════════
//  MicSample — Résultat d’une mesure micro (une boucle loop)
// ═══════════════════════════════════════════════════════════════
/*
 * Rempli par micSample() dans MicSensor.cpp à chaque passage dans la boucle.
 * Toutes les fonctions qui ont besoin du son reçoivent ce bloc (ou seulement .peak).
 *
 * Le plus important pour le VU et les flashs : champ « peak ».
 */
struct MicSample {
  int raw;     // Dernière lecture brute A0 (0-1023), peu utilisée
  int minVal;  // Minimum sur les SAMPLE_COUNT lectures de la fenêtre
  int maxVal;  // Maximum sur la fenêtre
  int avg;     // Moyenne sur la fenêtre (sert au lissage descente barre)
  int peak;    // Amplitude = maxVal - minVal → niveau sonore principal du VU
};
