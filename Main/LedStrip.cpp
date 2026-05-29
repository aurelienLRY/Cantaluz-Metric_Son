/*
 * LedStrip.cpp — Implémentation ruban WS2812B
 *
 * Principe affichage VU :
 *   - Plus le son est fort → plus de LED allumées depuis l'index 0 (DIN)
 *   - La couleur de chaque LED dépend de sa position (zone), pas du volume instantané
 */

#include "LedStrip.h"
#include "AppState.h"
#include "Config.h"

const CRGB COULEUR_VERT   = CRGB(0, 180, 0);
const CRGB COULEUR_ORANGE = CRGB(255, 140, 0);
const CRGB COULEUR_ROUGE  = CRGB(255, 0, 0);

void ledComputeZonesFromPlages() {
  int plageTotale = ADC_PLAGE_MAX - ADC_PLAGE_MIN + 1;
  if (plageTotale < 1) plageTotale = 1;

  int plageVert = g.live.adcFinZoneVert - ADC_PLAGE_MIN + 1;
  if (plageVert < 0) plageVert = 0;

  int plageOrange = g.live.adcFinZoneOrange - g.live.adcFinZoneVert;
  if (plageOrange < 0) plageOrange = 0;

  int plageRouge = ADC_PLAGE_MAX - g.live.adcFinZoneOrange;
  if (plageRouge < 0) plageRouge = 0;

  g.ledFinZoneVert = (LED_COUNT * (long)plageVert) / plageTotale;
  g.ledFinZoneOrange = g.ledFinZoneVert + (LED_COUNT * (long)plageOrange) / plageTotale;

  if (g.ledFinZoneVert < 1) g.ledFinZoneVert = 1;
  if (g.ledFinZoneOrange <= g.ledFinZoneVert) g.ledFinZoneOrange = g.ledFinZoneVert + 1;
  if (g.ledFinZoneOrange >= LED_COUNT) g.ledFinZoneOrange = LED_COUNT - 1;

  g.threshOrangeUp = g.live.adcFinZoneVert + 1;
  g.threshRedUp = g.live.adcFinZoneOrange + 1;
  g.threshGreenDn = g.live.adcFinZoneVert - ADC_HYST_VERT;
  g.threshOrangeDn = g.live.adcFinZoneOrange - ADC_HYST_ORANGE;
  if (g.threshGreenDn < ADC_PLAGE_MIN) g.threshGreenDn = ADC_PLAGE_MIN;
  if (g.threshOrangeDn <= g.threshGreenDn) g.threshOrangeDn = g.threshGreenDn + 1;
}

ColorState ledZoneDepuisPeak(int peak) {
  if (peak <= g.live.adcFinZoneVert) return STATE_GREEN;
  if (peak <= g.live.adcFinZoneOrange) return STATE_ORANGE;
  return STATE_RED;
}

ColorState ledStateWithHysteresis(int peak, ColorState cur) {
  switch (cur) {
    case STATE_GREEN:
      if (peak >= g.threshRedUp) return STATE_RED;
      if (peak >= g.threshOrangeUp) return STATE_ORANGE;
      return STATE_GREEN;

    case STATE_ORANGE:
      if (peak >= g.threshRedUp) return STATE_RED;
      if (peak < g.threshGreenDn) return STATE_GREEN;
      return STATE_ORANGE;

    case STATE_RED:
      if (peak < g.threshGreenDn) return STATE_GREEN;
      if (peak < g.threshOrangeDn) return STATE_ORANGE;
      return STATE_RED;
  }
  return STATE_GREEN;
}

CRGB ledCouleurPourIndex(int index) {
  if (index < g.ledFinZoneVert) return COULEUR_VERT;
  if (index < g.ledFinZoneOrange) return COULEUR_ORANGE;
  return COULEUR_ROUGE;
}

void ledRenderVuMeter(float level) {
  int litCount = MIN_LEDS_ON + (int)((LED_COUNT - MIN_LEDS_ON) * level + 0.5f);
  if (litCount < MIN_LEDS_ON) litCount = MIN_LEDS_ON;
  if (litCount > LED_COUNT) litCount = LED_COUNT;

  for (int i = 0; i < LED_COUNT; i++) {
    g.leds[i] = (i < litCount) ? ledCouleurPourIndex(i) : CRGB::Black;
  }
  FastLED.show();
  yield();
}

void ledFillStrip(CRGB color) {
  fill_solid(g.leds, LED_COUNT, color);
  FastLED.show();
  yield();
}

void ledAfficherBleuComplet(uint16_t dureeMs) {
  ledFillStrip(CRGB::Blue);
  for (uint16_t t = 0; t < dureeMs; t += 50) {
    delay(50);
    yield();
    ESP.wdtFeed();
  }
}

void ledInitHardware() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(g.leds, LED_COUNT);
  FastLED.setBrightness(g.live.maxBrightness);
  FastLED.clear(true);
}

void ledRunBootSequence() {
  for (float l = 0.0f; l <= 1.0f; l += 0.04f) {
    ledRenderVuMeter(l);
    delay(g.run.bootStepMs);
    yield();
    ESP.wdtFeed();
  }
  for (float l = 1.0f; l >= (float)MIN_LEDS_ON / (float)LED_COUNT; l -= 0.012f) {
    ledRenderVuMeter(l);
    delay(g.run.bootStepMs + 4);
    yield();
    ESP.wdtFeed();
  }

  g.displayLevel = (float)MIN_LEDS_ON / (float)LED_COUNT;
  g.currentState = STATE_GREEN;
  g.belowAvgSinceMs = 0;
  g.stateHoldSinceMs = 0;
  g.lastTransitionEndMs = millis();
}
