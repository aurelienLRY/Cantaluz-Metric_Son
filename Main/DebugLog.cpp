/*
 * DebugLog.cpp — Implémentation des traces série
 *
 * Nécessite Config.h avant DebugLog.h pour que DEBUG_SERIAL soit défini
 * (sinon ce fichier ne compile pas le corps de debugLogStatusIfDue).
 */

#include "Config.h"
#include "DebugLog.h"

#ifdef DEBUG_SERIAL

#include "AppState.h"
#include "FlashEtat.h"
#include "LedStrip.h"
#include "MicSensor.h"

void debugLogStatusIfDue(const MicSample &mic) {
  unsigned long now = millis();
  if (now - g.lastDebugMs < (unsigned long)DEBUG_INTERVAL_MS) {
    return;
  }
  g.lastDebugMs = now;

  int lit = MIN_LEDS_ON + (int)((LED_COUNT - MIN_LEDS_ON) * g.displayLevel);
  int peakEff = micPeakEffectifPourFlash(mic.peak);
  ColorState zonePlage = ledZoneDepuisPeak(peakEff);
  ColorState cible = flashProchainEtatMontee(zonePlage);

  Serial.println(F("----------"));
  Serial.print(F("peak="));
  Serial.print(mic.peak);
  Serial.print(F(" eff="));
  Serial.print(peakEff);
  Serial.print(F(" zone="));
  Serial.print(stateName(zonePlage));
  Serial.print(F(" etat="));
  Serial.print(stateName(g.currentState));
#if MODE_ACTIF == MODE_LENT
  Serial.println(F(" (mode lent — pas de flash bleu)"));
#else
  if (cible > g.currentState) {
    Serial.print(F(" -> flash "));
    Serial.println(stateName(cible));
    if (g.stateHoldSinceMs > 0) {
      Serial.print(F("attente flash "));
      Serial.print(now - g.stateHoldSinceMs);
      Serial.print(F("/"));
      Serial.println(STATE_HOLD_MS);
    }
  } else {
    Serial.println(F(" (pas de montee)"));
  }
  Serial.print(F("Flash si peak>"));
  Serial.print(ADC_FIN_ZONE_VERT);
  Serial.print(F(" (orange) ou >"));
  Serial.print(ADC_FIN_ZONE_ORANGE);
  Serial.println(F(" (rouge)"));
  if (g.transitionActive) {
    Serial.print(F(">>> FLASH step "));
    Serial.print(g.flashStep);
    Serial.print(F("/"));
    Serial.print(FLASH_COUNT * 2);
    Serial.println(F(" <<<"));
  }
#endif
  Serial.print(F("LED 0-"));
  Serial.print(g.ledFinZoneVert - 1);
  Serial.print(F("=VERT "));
  Serial.print(g.ledFinZoneVert);
  Serial.print(F("-"));
  Serial.print(g.ledFinZoneOrange - 1);
  Serial.print(F("=ORANGE "));
  Serial.print(g.ledFinZoneOrange);
  Serial.print(F("-"));
  Serial.print(LED_COUNT - 1);
  Serial.println(F("=ROUGE"));
  Serial.print(F("allumees="));
  Serial.println(lit);
}

#endif
