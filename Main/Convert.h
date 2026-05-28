#pragma once
/*
 * Convert.h — Utilitaires de conversion (Config.h → valeurs runtime)
 *
 * À quoi sert ce fichier ?
 * ------------------------
 * Transforme les réglages « humains » (% et secondes de Config.h)
 * en nombres utilisables par le code (fractions 0-1, millisecondes, etc.).
 *
 * Appelé par : configApply() dans AppState.cpp au démarrage.
 * Ne pas modifier sauf si vous ajoutez un nouveau type de réglage en %.
 */

#include <Arduino.h>

// Permet de convertir ATTACK_PERCENT, AVG_SMOOTH_PERCENT… en 0.0-1.0   entrée: [0 - 100]
inline float pctVersFraction(uint8_t pourcent) {
  if (pourcent > 100) pourcent = 100;
  return (float)pourcent / 100.0f;
}

// Permet de convertir DESCENT_DELAY_SEC, TRANSITION_COOLDOWN_SEC… en ms   entrée: [0 - 65535] s
inline unsigned long secVersMs(unsigned int secondes) {
  return (unsigned long)secondes * 1000UL;
}

// Permet de calculer la vitesse de descente de la barre (niveau/s) depuis DESCENT_DURATION_SEC   entrée: [1 - 600] s
inline float dureeVersTauxDescente(uint16_t secondesPourVider) {
  if (secondesPourVider < 1) secondesPourVider = 1;
  return 1.0f / (float)secondesPourVider;
}

// Permet de traduire BOOT_VU_SPEED_PERCENT en délai delay() pour l'anim boot   entrée: [5 - 100] → sortie [4 - 40] ms
inline uint8_t vitesseBootVersDelaiMs(uint8_t vitessePercent) {
  uint8_t v = vitessePercent;
  if (v < 5) v = 5;
  if (v > 100) v = 100;
  return (uint8_t)map(v, 100, 5, 4, 40);
}
