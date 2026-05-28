/*
 * ModeLent.cpp — VU doux sans flash bleu
 */

#include "ModeLent.h"
#include "AppState.h"
#include "Config.h"
#include "LedStrip.h"
#include "MicSensor.h"
#include "DebugLog.h"

void modeLentSetup() {
  ledComputeZonesFromPlages();

#ifdef DEBUG_SERIAL
  Serial.println(F("=== Mode LENT (dòç) ==="));
  Serial.print(F("Plages peak: vert 0-"));
  Serial.print(ADC_FIN_ZONE_VERT);
  Serial.print(F(" orange "));
  Serial.print(ADC_FIN_ZONE_VERT + 1);
  Serial.print(F("-"));
  Serial.print(ADC_FIN_ZONE_ORANGE);
  Serial.print(F(" rouge "));
  Serial.print(ADC_FIN_ZONE_ORANGE + 1);
  Serial.print(F("-"));
  Serial.println(ADC_PLAGE_MAX);
  Serial.println(F("Pas de flash bleu — montee/descente lentes."));
#endif

  ledInitHardware();
  FastLED.setBrightness(LENT_MAX_BRIGHTNESS);

#if LENT_BOOT_BLUE_MS > 0
  ledAfficherBleuComplet(LENT_BOOT_BLUE_MS);
#endif

  configApplyLent();

#ifdef DEBUG_SERIAL
  Serial.print(F("Lent: montee "));
  Serial.print(LENT_ATTACK_PERCENT);
  Serial.print(F("% descente apres "));
  Serial.print(LENT_DESCENT_DELAY_SEC);
  Serial.print(F("s pendant "));
  Serial.print(LENT_DESCENT_DURATION_SEC);
  Serial.println(F("s"));
#endif

  ledRunBootSequence();

#if USE_AUTO_VU_MAX
  micCalibrateVuMax();
#else
  g.vuMaxPeak = (MANUAL_VU_MAX > 0) ? MANUAL_VU_MAX : 500;
#endif

  g.peakSmooth = g.peakAverage;
  g.currentState = STATE_GREEN;
  g.transitionActive = false;
  g.lastLoopMs = millis();

#ifdef DEBUG_SERIAL
  Serial.println(F("Pret. Ambiance calme — barre fluide."));
#endif
}

void modeLentLoop() {
  unsigned long now = millis();
  float dtSec = (now - g.lastLoopMs) / 1000.0f;
  if (dtSec <= 0.0f) dtSec = 0.001f;
  g.lastLoopMs = now;

  MicSample mic;
  micSample(mic);
  micUpdatePeakSmooth(mic.peak);
  micUpdateDisplayLevel(mic.peak, dtSec);

  // Suivi silencieux du palier (debug / cohérence), sans flash
  int peakEff = micPeakEffectifPourFlash(mic.peak);
  g.currentState = ledStateWithHysteresis(peakEff, g.currentState);

  ledRenderVuMeter(g.displayLevel);

#ifdef DEBUG_SERIAL
  debugLogStatusIfDue(mic);
#endif
}
