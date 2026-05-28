#pragma once
/*
 * MicSensor.h — Micro MAX4466 (lecture, niveau barre, calibration)
 *
 * À quoi sert ce module ?
 * -----------------------
 *   - Lire le micro et produire un MicSample (surtout .peak)
 *   - Convertir le peak en hauteur de barre (displayLevel)
 *   - Calibrer le « bruit de fond » au boot pour la barre pleine
 *
 * Réglages liés : Config.h section MICRO et HAUTEUR BARRE VU
 * Dépend de : AppState (g), LedStrip (affichage pendant calibration)
 */

#include "Types.h"

// Permet de lire le micro et remplir out (peak = max-min sur SAMPLE_COUNT lectures)
void micSample(MicSample &out);

// Permet de lisser le peak pour les flashs (évite reset sur micro-coupures) — utilise PEAK_SMOOTH_PERCENT
void micUpdatePeakSmooth(int peak);

// Permet d'utiliser max(peak, peakSmooth) pour décider d'un flash bleu
int micPeakEffectifPourFlash(int peak);

// Permet de convertir le peak ADC en niveau 0.0-1.0 pour la hauteur de barre
float micPeakToLevel(int peak);

// Permet de mettre à jour g.displayLevel (montée rapide, descente après DESCENT_DELAY_SEC)
void micUpdateDisplayLevel(int peak, float dtSec);

// Permet de mesurer le silence au boot et fixer g.vuMaxPeak (si USE_AUTO_VU_MAX=1)
void micCalibrateVuMax();
