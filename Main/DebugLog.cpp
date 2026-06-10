/*
 * DebugLog.cpp — Traces série (DEBUG_SERIAL uniquement)
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

  int pEff = micPeakEffective(mic.peak);
  int peakFlash = micPeakEffectifPourFlash(pEff);
  ColorState zonePlage = ledZoneDepuisPeak(peakFlash);
  int lit = MIN_LEDS_ON + (int)((LED_COUNT - MIN_LEDS_ON) * g.displayLevel);

  Serial.println(F("----------"));
  Serial.print(F("raw="));
  Serial.print(mic.peak);
  Serial.print(F(" eff="));
  Serial.print(pEff);
  Serial.print(F(" barre="));
  Serial.print((int)(g.displayLevel * 100));
  Serial.print(F("% etat="));
  Serial.print(stateName(g.currentState));
  Serial.print(F(" zone="));
  Serial.println(stateName(zonePlage));
  Serial.print(F("Seuils vert<="));
  Serial.print(g.live.adcFinZoneVert);
  Serial.print(F(" orange<="));
  Serial.println(g.live.adcFinZoneOrange);
  Serial.print(F("LED allumees="));
  Serial.println(lit);
  if (g.transitionActive) {
    Serial.print(F("FLASH step "));
    Serial.println(g.flashStep);
  }
}

#endif
