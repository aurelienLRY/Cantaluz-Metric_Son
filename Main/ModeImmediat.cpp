/*
 * ModeImmediat.cpp — Enchaînement boot + boucle du mode immédiat
 *
 * Ordre au setup :
 *   zones LED → init FastLED → bleu boot → configApply → anim VU → sensibilité
 *
 * Ordre à chaque loop :
 *   flash en cours ? → sinon micro → niveau barre → machine flash → render VU
 */

#include "ModeImmediat.h"
#include "AppState.h"
#include "Config.h"
#include "LedStrip.h"
#include "MicSensor.h"
#include "FlashEtat.h"
#include "DebugLog.h"

void modeImmediatSetup() {
  ledComputeZonesFromPlages();

#ifdef DEBUG_SERIAL
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
  Serial.print(F("LED vert: 0-"));
  Serial.print(g.ledFinZoneVert - 1);
  Serial.print(F(" | orange: "));
  Serial.print(g.ledFinZoneVert);
  Serial.print(F("-"));
  Serial.print(g.ledFinZoneOrange - 1);
  Serial.print(F(" | rouge: "));
  Serial.print(g.ledFinZoneOrange);
  Serial.print(F("-"));
  Serial.println(LED_COUNT - 1);
  Serial.print(F("Flash: orange si peak>"));
  Serial.print(ADC_FIN_ZONE_VERT);
  Serial.print(F(" rouge si peak>"));
  Serial.println(ADC_FIN_ZONE_ORANGE);
#endif

  ledInitHardware();
  ledAfficherBleuComplet(BOOT_BLUE_MS);

#ifdef DEBUG_SERIAL
  Serial.println(F("Boot: bandeau bleu OK"));
#endif

  configApply();

#ifdef DEBUG_SERIAL
  Serial.print(F("Config: montee "));
  Serial.print(ATTACK_PERCENT);
  Serial.print(F("% descente apres "));
  Serial.print(DESCENT_DELAY_SEC);
  Serial.print(F("s pendant "));
  Serial.print(DESCENT_DURATION_SEC);
  Serial.println(F("s"));
#endif

  ledRunBootSequence();

  micInitVuFromSettings();
  g.lastLoopMs = millis();

#ifdef DEBUG_SERIAL
  Serial.print(F("Micro: sens="));
  Serial.print(g.live.sensitivity);
  Serial.print(F(" gate="));
  Serial.print(g.micGate);
  Serial.print(F(" span="));
  Serial.println(g.micSpan);
  Serial.print(F("Seuils eff. vert<="));
  Serial.print(g.live.adcFinZoneVert);
  Serial.print(F(" orange<="));
  Serial.println(g.live.adcFinZoneOrange);
  Serial.println(F("Pret. Voix forte -> montee + flash bleu si palier."));
#endif
}

void modeImmediatLoop() {
  static unsigned long s_lastFrameMs = 0;
  unsigned long now = millis();
  if (now - s_lastFrameMs < (unsigned long)LOOP_MIN_PERIOD_MS) {
    yield();
    return;
  }
  s_lastFrameMs = now;

  float dtSec = (now - g.lastLoopMs) / 1000.0f;
  if (dtSec <= 0.0f) dtSec = 0.001f;
  g.lastLoopMs = now;

  if (g.transitionActive) {
    flashUpdateTransition();
    return;
  }

  MicSample mic;
  micSample(mic);
  int peak = micPeakEffective(mic.peak);
  g.lastPeak = peak;
  g.lastMicAvg = mic.avg;
  micUpdatePeakSmooth(peak);
  micUpdateDisplayLevel(peak, dtSec);
  flashHandleStateMachine(peak);

  if (!g.transitionActive) {
    ledRenderVuMeter(g.displayLevel);
  }

#ifdef DEBUG_SERIAL
  debugLogStatusIfDue(mic);
#endif
}
