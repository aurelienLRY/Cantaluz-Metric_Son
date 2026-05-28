/*
 * FlashEtat.cpp — Machine d'états des flashs bleus
 *
 * Pendant transitionActive == true, ModeImmediat n'affiche pas le VU
 * et appelle uniquement flashUpdateTransition().
 */

#include "FlashEtat.h"
#include "AppState.h"
#include "Config.h"
#include "LedStrip.h"
#include "MicSensor.h"

ColorState flashProchainEtatMontee(ColorState zonePlage) {
  if (zonePlage <= g.currentState) {
    return g.currentState;
  }
  ColorState suivant = (ColorState)((uint8_t)g.currentState + 1);
  if (suivant > zonePlage) {
    suivant = zonePlage;
  }
  return suivant;
}

void flashStartTransition(ColorState newState) {
  g.transitionActive = true;
  g.pendingState = newState;
  g.flashStep = 0;
  g.lastFlashMs = millis();
  ledFillStrip(CRGB::Blue);

#ifdef DEBUG_SERIAL
  Serial.print(F("[FLASH BLEU] montee -> "));
  Serial.println(stateName(newState));
#endif
}

bool flashUpdateTransition() {
  unsigned long now = millis();

  if (g.flashStep >= (uint8_t)(FLASH_COUNT * 2)) {
    g.currentState = g.pendingState;
    g.transitionActive = false;
    g.lastTransitionEndMs = now;
    ledRenderVuMeter(g.displayLevel);
    return true;
  }

  unsigned long duree = (g.flashStep % 2 == 0) ? (unsigned long)FLASH_ON_MS
                                               : (unsigned long)FLASH_OFF_MS;
  if (now - g.lastFlashMs < duree) {
    return false;
  }

  if (g.flashStep % 2 == 0) {
    ledFillStrip(CRGB::Blue);
  } else {
    fill_solid(g.leds, LED_COUNT, CRGB::Black);
    FastLED.show();
  }

  g.flashStep++;
  g.lastFlashMs = now;
  return false;
}

void flashHandleStateMachine(int peak) {
  unsigned long now = millis();
  int peakEff = micPeakEffectifPourFlash(peak);

  ColorState zonePlage = ledZoneDepuisPeak(peakEff);
  ColorState zoneDescente = ledStateWithHysteresis(peak, g.currentState);
  ColorState cibleFlash = flashProchainEtatMontee(zonePlage);

  if (zoneDescente < g.currentState) {
    g.currentState = zoneDescente;
    g.holdTarget = g.currentState;
    g.stateHoldSinceMs = 0;
    g.belowZoneSinceMs = 0;
    return;
  }

  if (cibleFlash <= g.currentState) {
    if (g.belowZoneSinceMs == 0) {
      g.belowZoneSinceMs = now;
    }
    if (now - g.belowZoneSinceMs < (unsigned long)FLASH_HOLD_RESET_MS) {
      return;
    }
    g.holdTarget = cibleFlash;
    g.stateHoldSinceMs = 0;
    g.belowZoneSinceMs = 0;
    return;
  }

  g.belowZoneSinceMs = 0;

  if (cibleFlash != g.holdTarget) {
    g.holdTarget = cibleFlash;
    g.stateHoldSinceMs = now;
    return;
  }

  if (g.stateHoldSinceMs == 0) {
    g.stateHoldSinceMs = now;
    return;
  }

  if (now - g.stateHoldSinceMs < (unsigned long)STATE_HOLD_MS) {
    return;
  }
  if (now - g.lastTransitionEndMs < g.run.transitionCooldownMs) {
    return;
  }

  flashStartTransition(cibleFlash);
  g.stateHoldSinceMs = 0;
}
